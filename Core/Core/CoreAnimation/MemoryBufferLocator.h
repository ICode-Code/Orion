#ifndef OE1_ANIMATION_BUFFER_LOCATOR_H_
#define OE1_ANIMATION_BUFFER_LOCATOR_H_


namespace OE1Core
{
    struct MemoryBufferLocator
    {
        // Identifies which uniform buffer this data belongs to from an array of buffer
        int BufferIndex = 0;

        /// <summary>
        /// ID of the buffer needed to bind when updating sub-data, such as bone transforms
        /// </summary>
        unsigned int BufferID = 0;

        /// <summary>
        /// Offset in memory, e.g., sizeof(glm::mat4) * NumberOfBone
        /// </summary>
        size_t Offset = 0;

        /// <summary>
        /// The begining of the read/write offset
        /// </summary>
        size_t BaseOffset = 0;

        /// <summary>
        /// Number of bones; useful in certain instances
        /// </summary>
        int BoneCount = 0;
    };

}

#endif // !OE1_ANIMATION_BUFFER_LOCATOR_H_
