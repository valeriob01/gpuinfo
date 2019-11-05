#include <cstdlib>
#include <cstring>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


static gpuinfo::gpu::vendor_t parse_vendor(const char* name) {
	if(!std::strcmp(name, "Intel(R) Corporation"))
		return gpuinfo::gpu::vendor_t::intel;
	else if(!std::strcmp(name, "Advanced Micro Devices, Inc."))
		return gpuinfo::gpu::vendor_t::amd;
	else if(!std::strcmp(name, "NVIDIA Corporation"))
		return gpuinfo::gpu::vendor_t::nvidia;
	else
		return gpuinfo::gpu::vendor_t::unknown;
}


std::vector<gpuinfo::gpu::device_properties_t> gpuinfo::gpu::device_properties(cl_uint device) {
	char name[256];
	char vendorname[256];
	cl_ulong cache;
	cl_ulong memory;
	cl_uint max_frequency;

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cache), &cache, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_frequency), &max_frequency, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(memory), &memory, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendorname) / sizeof(*vendorname), &vendorname, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name) / sizeof(*name), &name, nullptr);

	ret.push_back({parse_vendor(vendorname), name, memory, cache, max_frequency * 1'000'000});
	
	return ret;
}
