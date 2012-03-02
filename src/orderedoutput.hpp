#ifndef ORDEREDOUTPUT_HPP
#define ORDEREDOUTPUT_HPP

#include <string>
#include <map>
#include <mutex>
#include <thread>

#include "blockingqueue.hpp"

class OrderedOutput
{
public:
	struct Chunk
	{
		unsigned int id;
		std::string result;
	};

	OrderedOutput(size_t memoryLimit, size_t flushThreshold);
	~OrderedOutput();

    Chunk* begin(unsigned int id);
    void write(Chunk* chunk, const char* format, ...);
    void end(Chunk* chunk);

private:
	BlockingQueue<Chunk*> writeQueue;
	std::thread writeThread;

	size_t flushThreshold;

	std::mutex mutex;
	unsigned int currentChunk;
	std::map<unsigned int, Chunk*> chunks;
};

#endif