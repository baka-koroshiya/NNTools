#pragma once
#include <fnd/Vec.h>
#include <fnd/IFile.h>
#include <fnd/SharedPtr.h>


class CachedIFile : public fnd::IFile
{
public:
	CachedIFile(const fnd::SharedPtr<fnd::IFile>& file, size_t block_size, size_t block_num);

	size_t size();
	void seek(size_t offset);
	void read(byte_t* out, size_t len);
	void read(byte_t* out, size_t offset, size_t len);
	void write(const byte_t* out, size_t len);
	void write(const byte_t* out, size_t offset, size_t len);
private:
	struct sCacheBlockInfo
	{
		sCacheBlockInfo(size_t block_index, size_t cache_offset)
		{
			this->block_index = block_index;
			this->cache_offset = cache_offset;
		}

		size_t block_index;
		size_t cache_offset;
	};

	// file
	fnd::SharedPtr<fnd::IFile> mFile;

	// virtual offset in file
	size_t mOffset;

	// information about block size and num
	size_t mBlkSize;
	size_t mBlkNum;
	
	// cache memory
	fnd::Vec<byte_t> mCache;

	// cache management
	fnd::Vec<size_t> mBlkVAddr;
};


/*
class ManagedCache
	{
		ManagedCache();

		size_t getBlockSize() const;
		void setBlockSize(size_t block_size);

		size_t getBlockCacheCapacity();
		void setBlockCacheCapacity(size_t num);

		bool hasBlock(size_t blk_idx) const;
		const fnd::SharedPtr<byte_t>& getBlock(size_t blk_index);
		

	private:
		size_t m_Block;
		fnd::Vec<byte_t> m_Cache;
	};
*/