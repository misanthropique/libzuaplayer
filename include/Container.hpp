/**
 * Copyright ©2021. Brent Weichel. All Rights Reserved.
 * Permission to use, copy, modify, and/or distribute this software, in whole
 * or part by any means, without express prior written agreement is prohibited.
 */
#pragma once

#include <vector>

#include "File.hpp"
#include "StreamMetadata.hpp"
#include "Packet.hpp"

namespace ZuaPlayer
{

/**
 * Logical abstraction for a Container file.
 * A container is a file format used for the purpose of
 * storing and, typically, interleaving related data such as
 * audio, video, and sub-titles. The derived class may also
 * contain just a single data type. E.g. a FLAC container
 * would packetize frames from a FLAC audio file.
 */
class Container
{
public:
	/**
	 * Default constructor has been deleted.
	 */
	Container() = delete;

	/**
	 * File constructor for Container. The file object will be in data persistence mode
	 * when passed into the constructor, assuming that the Container recognizes the contents
	 * of the file, the file will be removed from that mode and reading can resume like normal.
	 * @param file Constant reference to a File object.
	 * @throw std::runtime_error shall be thrown if the derived subclass does not
	 *        recognize the contents of the file.
	 */
	Container( const File& file );

	/**
	 * Default virtual destructor to ensure that the derived class's destruct is called.
	 */
	virtual ~Container() = default;

	/**
	 * Read a packet of data from the container and return true upon success.
	 * @param packet Reference to a PacketPointer to which a data packet is to be assigned.
	 * @return True is returned if {@param packet} was assigned data without error.
	 */
	virtual bool readPacket( PacketPointer& packet ) = 0;

	/**
	 * Retrieve the vector of available streams and any relevant metadata.
	 * @return A std::vector of StreamMetadata object describing streams present in the container is returned.
	 */
	virtual std::vector< StreamMetadata > getAvailableStreams() = 0;
};

} // namespace ZuaPlayer
