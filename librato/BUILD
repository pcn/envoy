# -*- python -*-

# Provide a build target for building the static release binary and turning it into a deb


# Build a .deb of envoy

load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar", "pkg_deb")

# For this to fly we need the release to be built like this:
# bazel --bazelrc=/dev/null build -c opt //source/exe:envoy-static.stripped.stamped

# genrule(name, srcs, outs, cmd, compatible_with, deprecation, distribs, executable, features, licenses, local, message, output_licenses, output_to_bindir, restricted_to, tags, testonly, tools, visibility)

genrule(
    name = "rename-binary",
    srcs = ["//source/exe:envoy-static.stripped.stamped"],
    outs = ["envoy"],
    cmd = "cp -f $(location //source/exe:envoy-static.stripped.stamped) $@; chmod u+w $@; strip $@",
)

genrule(
    name = "debian-version",
    srcs = [],
    outs = ["deb_version_file"],
    cmd = "echo $$(grep BUILD_SCM_DESCRIPTION bazel-out/volatile-status.txt | cut -d' ' -f2)-$$(grep BUILD_SCM_STATUS bazel-out/volatile-status.txt | cut -d' ' -f2) > $@",
    stamp = 1  # stamp makes the volatile-status available, apparently
)


genrule(
    name = "copy_resources",
    srcs = ["//restarter:restarter_resources"],
    outs = [ "hot-restarter.py" ],
    cmd = "cp -f $(SRCS) $@",
)


pkg_tar(
    name = "envoy-bin",
    strip_prefix = "/librato",
    package_dir = "/opt/envoy/bin", 
    srcs = [":rename-binary"],
    mode = "0755",
)

pkg_tar(
    name = "envoy-restarter",
    strip_prefix = "/restarter",
    package_dir = "/opt/envoy/bin", 
    srcs = ["//restarter:restarter_resources"],
    mode = "0755",
)


pkg_tar(
    name = "envoy-data",
    extension = ".tar.gz",
    deps = [":envoy-bin", ":envoy-restarter"],
)


pkg_deb(
    name = "envoy-debian",
    architecture = "amd64",
    built_using = "bazel",
    data = ":envoy-data",
    description = "Lyft envoy mostly static binary; stripped",
    homepage = "https://github.com/envoyproxy/envoy",
    maintainer = "Lyft (packaged by https://github.com/pcn)",
    package = "lyft-envoy",
    version = "1.5.0-librato2"
    # version_file = ":debian-version",  # version_file is useless until https://github.com/bazelbuild/bazel/issues/3652 is fixed
)
