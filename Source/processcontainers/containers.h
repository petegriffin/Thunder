#ifndef __CONTAINERS_H
#define __CONTAINERS_H

#include <stdint.h>
#include <string.h>

#define EXTERNAL

/**
 * Sometimes the compiler would like to be smart, if we do not reference
 * anything here
 * and you enable the rightflags, the linker drops the dependency. Than
 * Proxy/Stubs do
 * not get loaded, so lets make the instantiation of the ProxyStubs explicit !!!
 */
extern "C" {
EXTERNAL void ForceLinkingOfOpenCDM();
}
#else
#define EXTERNAL
#endif

#ifdef __cplusplus

extern "C" {

#endif

struct Container;

/**
 * OpenCDM error code. Zero always means success.
 */
typedef enum {
    ERROR_NONE = 0,
    ERROR_UNKNOWN = 1,
    ERROR_MORE_DATA_AVAILBALE=2,
} ContainerError;

struct ContainerMemory {
    uint64_t allocated; // in bytes
    uint64_t resident; // in bytes
    uint64_t shared; // in bytes
};

/**
 * \brief Initializes a container.
 *
 * This function initializes a container and prepares it to be started
 * \param container Container that is to be initialized
 * \param name Name of started container
 * \param searchpaths Null-terminated list of locations where container can be located. 
 * List is processed in the order it is provided, and the first container of given Name 
 * found is initialized
 * \return Zero on success, non-zero on error.
 */
EXTERNAL ContainerError container_init(struct Container* container, char* name, char** searchpaths);

/**
 * \brief Deinitializes a container.
 *
 * This function deinitializes a container, effectively releasing
 * all resources taken by it
 * \param container Container that is to be initialized
 * \return Zero on success, non-zero on error.
 */
EXTERNAL ContainerError container_deinit(struct Container* container);

/**
 * \brief Starts a container.
 *
 * This function starts a given command in the container
 * \param container Container that is to be initialized
 * \param command Command that will be started in container's shell
 * \params Null-terminated list of parameters provied to command
 * \return Zero on success, non-zero on error.
 */
EXTERNAL ContainerError container_start(struct Container* container, char* command, char** params);

/**
 * \brief Stops a container.
 *
 * This function stops a container
 * \param container Container that is to be initialized
 * \return Zero on success, non-zero on error.
 */
EXTERNAL ContainerError container_stop(struct Container* container);

/**
 * \brief Gives information if the container is running.
 *
 * This function can be used to check if container is in stopped state
 * or in running state.
 * \param container Container that is checked
 * \return 1 if is running, 0 otherwise.
 */
EXTERNAL uint8_t container_isrunning(struct Container* container);

/**
 * \brief Information about memory usage.
 *
 * Function gives information about memory allocated to 
 * runnning the container
 * \param container Container that is checked
 * \param memory Pointer to structure that will be filled with memory 
 * information
 * \return Zero on success, error-code otherwise
 */
EXTERNAL ContainerError container_memory(struct Container* container, ContainerMemory* memory);

/**
 * \brief Number of container's network interfaces.
 *
 * Function gives number of network interfaces assigned to the container
 * \param container Container that is checked
 * \return Number of networks assigned to interface
 */
EXTERNAL uint32_t container_numnetworks(struct Container* container);

/**
 * \brief Name of network interface.
 *
 * Function gives name of network interface asssigend to the container
 * \param networkID id of network interface. Might vary from 0 to number returned by container_numnetworks(struct Container*)
 * \param networkName pointer to buffer where network name will be stored. 
 * \return Number of networks assigned to interface. Buffer must be at least IFNAMSIZ long (usually 16 characters, including null terminator)
 * 
 * TODO: Add better buffer length handling
 */
EXTERNAL ContainerError container_interfacename(struct Container* container, uint32_t networkID, char* networkName);

/**
 * \brief Number of container's network interfaces.
 *
 * Function gives number of ips assigned to interface
 * \param container Container that is checked
 * \param interface Name of interface taht is cheked for the number of ips. If NULL is 
 * provided, function will return number of all ips assigned to container
 * \return Number of networks assigned to interface
 */
EXTERNAL uint32_t container_numips(struct Container* container, char* interface);

/**
 * \brief Interface ip address
 *
 * Function gives list of ips assigned to container's network interface
 * \param interface id of network interface. Might vary from 0 to number returned by container_numnetworks(struct Container*)
 * \param networkName pointer to buffer where network name will be stored. 
 * \return Number of networks assigned to interface. Buffer must be at least IFNAMSIZ long (usually 16 characters, including null terminator)
 */
EXTERNAL ContainerError container_ips(struct Container* container, char* interface, uint32_t* ips);


#ifdef __cplusplus
}
#endif

#endif // __CONTAINERS_H
