#include <cstdint>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

namespace gpu {
	enum class vendor_t {
		intel,
		amd,
		nvidia,
		microsoft,
		qualcomm,
		unknown,
	};
	struct device_properties_t {
		vendor_t vendor;
		std::string name;
		std::size_t memory_size;
		std::size_t cache_size;
		std::uint64_t max_frequency;
	};


	/// Returns all GPU's properties.
	std::vector<device_properties_t> device_properties(cl_device_id device);
}  // namespace gpu

static gpu::vendor_t parse_vendor(const char* name) {
	if(!std::strcmp(name, "Intel(R) Corporation"))
		return gpu::vendor_t::intel;
	else if(!std::strcmp(name, "Advanced Micro Devices, Inc."))
		return gpu::vendor_t::amd;
	else if(!std::strcmp(name, "NVIDIA Corporation"))
		return gpu::vendor_t::nvidia;
	else
		return gpu::vendor_t::unknown;
}


std::vector<gpu::device_properties_t> gpu::device_properties(cl_device_id device) {
	char name[256];
	char vendorname[256];
	cl_ulong cache;
	cl_ulong memory;
	cl_uint max_frequency;
	std::vector<gpu::device_properties_t> ret;

	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_CACHE_SIZE, sizeof(cache), &cache, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(max_frequency), &max_frequency, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(memory), &memory, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_VENDOR, sizeof(vendorname) / sizeof(*vendorname), &vendorname, nullptr);
	clGetDeviceInfo(device, CL_DEVICE_NAME, sizeof(name) / sizeof(*name), &name, nullptr);

	ret.push_back({parse_vendor(vendorname), name, memory, cache, max_frequency * 1'000'000});
	
	return ret;
}

