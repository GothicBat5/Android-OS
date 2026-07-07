exit_code=0
for dist_dir in "$@"
do
    abi_report_path="${dist_dir}/abi_stgdiff/abi.report.short"
    abi_report=$(cat "${abi_report_path}")
    if [ -n "${abi_report}" ]; then
        echo 'ERROR: ABI DIFFERENCES HAVE BEEN DETECTED!' >&2
        echo "ERROR: From ${abi_report_path}:" >&2
        echo >&2
        cat "${abi_report_path}" >&2
        exit_code=1
    else
        echo "INFO: no ABI differences reported in ${abi_report_path}."
    fi
done
exit ${exit_code}
