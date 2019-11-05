#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace gpuinfo {
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
		std::vector<device_properties_t> device_properties(cl_uint device);
	}  // namespace gpu
} // namespace gpuinfo
