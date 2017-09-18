#pragma once
#include <cstdint>
#include <queue>

class PSBuffer
{
public:
	PSBuffer();
	~PSBuffer();

	struct BufferNode
	{
		BufferNode()
		{
			data_ = new uint8_t[1024 * 1024 * 20];
		}

		BufferNode(BufferNode && other)
			:destip_(std::move(other.destip_)), destport_(other.destport_), data_(other.data_),length_(other.length_)
		{
			other.data_ = nullptr;
			other.length_ = 0;
		}
		BufferNode & operator=(BufferNode && other)
		{
			destip_ = std::move(other.destip_);
			destport_ = other.destport_;
			length_ = other.length_;
			data_ = other.data_;

			other.data_ = nullptr;
			other.length_ = 0;
			return *this;
		}

		BufferNode(const BufferNode & other) = delete;
		BufferNode & operator=(const BufferNode & other) = delete;

		~BufferNode()
		{
			if (data_)
			{
				delete[] data_;
			}
		}
		std::string destip_;
		uint32_t destport_;
		uint32_t length_;
		uint8_t * data_;
	};
private:
	std::queue<BufferNode> freeChain_;
	std::queue<BufferNode> busyChain_;
};

PSBuffer::PSBuffer()
{
}

PSBuffer::~PSBuffer()
{
}
