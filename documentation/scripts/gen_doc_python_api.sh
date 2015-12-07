#!/bin/bash

CURRENT_DIR=$(dirname ${BASH_SOURCE[0]})

doxy_conf_file="${CURRENT_DIR}/../doxy_conf/doxy_python_api.conf"
out_dir_default="${HOME}/rapp_platform_files/documentation/api/"

if [ -z "$1" ]; then
  out_dir=${out_dir_default}
else
  out_dir="$1"
fi

# Create output directory if it does not exist
mkdir -p ${out_dir}

match_str="OUTPUT_DIRECTORY"
append_str="${match_str} = ${out_dir}"

# Remove match_str line from doxy_conf_file
sed -i "/${match_str}/d" ${doxy_conf_file}

grep -q "${match_str}" "${doxy_conf_file}" || \
  echo -e "${append_str}" >> ${doxy_conf_file}

# Redirect stdout.
doxygen ${doxy_conf_file} &> /dev/null

cd ${out_dir_default}
cd latex
make &> /dev/null
cp refman.pdf ../api_rapp.pdf
