#pragma once
#include <string>
#include <fnd/types.h>
#include <fnd/List.h>
#include <crypto/sha.h>
#include <fnd/ISerialiseableBinary.h>

namespace nx
{
	namespace nso
	{
		const std::string kNsoSig = "NSO0";

		enum HeaderFlags
		{
			FLAG_TEXT_COMPRESS,
			FLAG_RO_COMPRESS,
			FLAG_DATA_COMPRESS,
			FLAG_TEXT_HASH,
			FLAG_RO_HASH,
			FLAG_DATA_HASH
		};

		static const uint32_t kDefaultFormatVersion = 0;
		static const size_t kModuleIdLen = 32;
	}
	
#pragma pack(push,1)
	struct sNsoCodeSegment
	{
		le_uint32_t file_offset;
		le_uint32_t memory_offset;
		le_uint32_t size;
	};

	struct sNsoSection
	{
		le_uint32_t offset;
		le_uint32_t size;
	};

	struct sNsoHeader
	{
		char signature[4];
		le_uint32_t format_version;
		byte_t reserved_1[4];
		le_uint32_t flags;
		sNsoCodeSegment text;
		le_uint32_t module_name_offset;
		sNsoCodeSegment ro;
		le_uint32_t module_name_size;
		sNsoCodeSegment data;
		le_uint32_t bss_size;
		byte_t module_id[nso::kModuleIdLen];
		le_uint32_t text_file_size;
		le_uint32_t ro_file_size;
		le_uint32_t data_file_size;
		byte_t reserved_2[28];
		sNsoSection embedded;
		sNsoSection dyn_str;
		sNsoSection dyn_sym;
		crypto::sha::sSha256Hash text_hash;
		crypto::sha::sSha256Hash ro_hash;
		crypto::sha::sSha256Hash data_hash;
	};

#pragma pack(pop)
}