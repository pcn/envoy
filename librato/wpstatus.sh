#!/bin/bash

# Match the workplace status of the rest of the build


if [ -f SOURCE_VERSION ]
then
    echo "BUILD_SCM_REVISION $(cat SOURCE_VERSION)"
    echo "BUILD_SCM_STATUS Distribution"
    exit 0
fi

# The code below presents an implementation that works for git repository
git_rev=$(git rev-parse HEAD)
if [[ $? != 0 ]];
then
    exit 1
fi
echo "BUILD_SCM_REVISION ${git_rev}"

git_description=$(git describe --tags --dirty)
echo "BUILD_SCM_DESCRIPTION ${git_description}"

# Check whether there are any uncommited changes
git diff-index --quiet HEAD --
if [[ $? == 0 ]];
then
    tree_status="Clean"
else
    tree_status="Modified"
fi
echo "BUILD_SCM_STATUS ${tree_status}"
