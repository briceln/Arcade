/*
** EPITECH PROJECT, 2021
** cpp_arcade
** File description:
** Created by asianpw,
*/

#define GLFW_INCLUDE_VULKAN
#define GLFW_DLL
#include <GLFW/glfw3.h>
#include <iostream>
#include <cstring>
#include <set>
#include <limits>
#include "Vulkan.hpp"
#include "../../../inc/ArcadeException.hpp"

// When I wrote this,
// only God and I understood what I was doing
// Now, God only knows

VkResult	CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	} else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void	DestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks* pAllocator) {
	auto func = (PFN_vkDestroyDebugReportCallbackEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, callback, pAllocator);
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL	debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userData) {
	std::cerr << "validation layer: " << msg << std::endl;
	(void)flags;
	(void)objType;
	(void)obj;
	(void)location;
	(void)code;
	(void)layerPrefix;
	(void)userData;
	return VK_FALSE;
}

void	Vulkan::setupDebugCallback() {
	if (!enableValidationLayers)
		return;
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;
	if (CreateDebugReportCallbackEXT(instance, &createInfo, nullptr, &callback) != VK_SUCCESS) {
		throw arcade::GraphicsLibraryError("failed to set up debug callback!");
	}
}

std::vector<const char*>	Vulkan::getRequiredExtensions() {
	uint32_t glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	std::vector<const char*> extensions(glfwExtensions, glfwExtensions + glfwExtensionCount);

	if (enableValidationLayers) {
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
	}

	return extensions;
}

bool	Vulkan::checkValidationLayerSupport()
{
	bool		layerFound;
	uint32_t	layerCount;
	std::vector<VkLayerProperties>	availableLayers;

	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	availableLayers.resize(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());
	for (const char *layerName : validationLayers) {
		layerFound = false;
		for (auto const &layerProperties : availableLayers) {
			if (strcmp(layerName, layerProperties.layerName) == 0) {
				layerFound = true;
				break;
			}
		}
		if (!layerFound) {
			return false;
		}
	}
	return true;
}

Vulkan::Vulkan(size_t width, size_t height) : physicalDevice(VK_NULL_HANDLE), width(width), height(height)
{
	glfwInit();
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	window = glfwCreateWindow(width, height, "Arcade - Vulkan", nullptr, nullptr);
	if (!window)
		throw arcade::GraphicsLibraryError("Vulkan: error while init window");
	initVulkanApi();
	if (glfwVulkanSupported())
		std::cerr << "Vulkan Supported" << std::endl;
	allEvent.insert({arcade::ESCAPE, GLFW_KEY_ESCAPE});
	allEvent.insert({arcade::UP, GLFW_KEY_UP});
	allEvent.insert({arcade::LEFT, GLFW_KEY_LEFT});
	allEvent.insert({arcade::DOWN, GLFW_KEY_DOWN});
	allEvent.insert({arcade::RIGHT, GLFW_KEY_RIGHT});
	keyPress = false;
	change = false;
	switchScene = false;
	windowDestroy = false;
}

Vulkan::~Vulkan()
{
	glfwTerminate();
}

bool	Vulkan::GetKey(arcade::TypeEvent typeEvent, std::string const &currentEvent)
{
	(void)typeEvent;
	for (auto const &key : allEvent) {
		if (key.first == currentEvent && glfwGetKey(window, key.second) == GLFW_PRESS) {
			return true;
		}
	}
	return false;
}

bool	Vulkan::isKey()
{
	glfwPollEvents();
	keyPress = !keyPress;
	return keyPress;
}

bool	Vulkan::isOpen()
{
	return !windowDestroy;
}

bool	Vulkan::Display()
{
	return false;
}

void	Vulkan::destroyWindow()
{
	if (!windowDestroy) {
		vkDestroySwapchainKHR(device, swapChain, nullptr);
		vkDestroyDevice(device, nullptr);
		if (enableValidationLayers) {
			DestroyDebugReportCallbackEXT(instance, callback, nullptr);
		}
		vkDestroySurfaceKHR(instance, surface, nullptr);
		vkDestroyInstance(instance, nullptr);
		glfwDestroyWindow(window);
	}
	windowDestroy = true;
}

bool Vulkan::loadText(std::map<std::string, Texture> const& text)
{
	(void)text;
	return false;
}

bool Vulkan::loadTexture(std::map<std::string, Texture> const& texture)
{
	(void)texture;
	return false;
}

void Vulkan::changeLibrary(std::string const &path)
{
	change = true;
	newLibraryPath = path;
}

bool Vulkan::getChange() const
{
	return change;
}

void Vulkan::setChange(bool state)
{
	change = state;
}

const std::string &Vulkan::getLibraryPath() const
{
	return newLibraryPath;
}

bool Vulkan::loadMap(std::vector<std::vector<char>> const &map)
{
	(void)map;
	return false;
}

const std::string &Vulkan::getNewGamePath() const
{
	return newGamePath;
}

void Vulkan::setNewGamePath(std::string const &path)
{
	newGamePath = path;
}

bool Vulkan::getSwitchScene() const
{
	return switchScene;
}

void Vulkan::setSwitchScene(bool state)
{
	switchScene = state;
}

void	Vulkan::initVulkanApi()
{
	appInfo = {};
	createInfo = {};
	createInstance();
	setupDebugCallback();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
}

void	Vulkan::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	std::vector<VkPhysicalDevice> devices(deviceCount);

	vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		throw arcade::GraphicsLibraryError("failed to find GPUs with Vulkan support!");
	}
	devices.resize(deviceCount);
	vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());
	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			physicalDevice = device;
			break;
		}
	}
	if (physicalDevice == VK_NULL_HANDLE) {
		throw arcade::GraphicsLibraryError("failed to find a suitable GPU!");
	}
}

bool	Vulkan::isDeviceSuitable(VkPhysicalDevice device)
{
	return findQueueFamilies(device).isComplete;
}

QueueFamilyIndices	Vulkan::findQueueFamilies(VkPhysicalDevice device)
{
	QueueFamilyIndices	indices;
	uint32_t	count = 0;
	uint32_t	queueFamilyCount = 0;
	VkBool32	presentSupport = VK_FALSE;
	std::vector<VkQueueFamilyProperties>	queueFamilies;

	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	queueFamilies.resize(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());
	for (const auto& queueFamily : queueFamilies) {
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = count;
		}
		vkGetPhysicalDeviceSurfaceSupportKHR(device, count, surface, &presentSupport);
		if (queueFamily.queueCount > 0 && presentSupport)
			indices.presentFamily = count;
		if (indices.graphicsFamily >= 0 && indices.presentFamily >= 0) {
			break;
		}
		count++;
	}
	indices.isComplete = indices.graphicsFamily >= 0 && indices.presentFamily >= 0;
	return indices;
}

void	Vulkan::initVulkanInfo()
{
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Arcade";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "No Engine";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
	createInfo.ppEnabledExtensionNames = extensions.data();
}

void	Vulkan::createInstance()
{

	if (enableValidationLayers && !checkValidationLayerSupport())
		throw arcade::GraphicsLibraryError("validation layers requested, but not available!");
	extensions = getRequiredExtensions();
	initVulkanInfo();
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else
		createInfo.enabledLayerCount = 0;
	if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS)
		throw arcade::GraphicsLibraryError("failed to create instance!");
}

void	Vulkan::createLogicalDevice()
{
	QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int>	uniqueQueueFamilies = {indices.graphicsFamily, indices.presentFamily};
	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	VkDeviceQueueCreateInfo queueCreateInfo = {};
	float queuePriority = 1.0f;

	for (auto queueFamily : uniqueQueueFamilies) {
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.emplace_back(queueCreateInfo);
	}
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = 0;
	if (enableValidationLayers) {
		createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
		createInfo.ppEnabledLayerNames = validationLayers.data();
	} else {
		createInfo.enabledLayerCount = 0;
	}
	if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS) {
		throw std::runtime_error("failed to create logical device!");
	}
	vkGetDeviceQueue(device, (uint32_t)indices.graphicsFamily, 0, &graphicsQueue);
	vkGetDeviceQueue(device, (uint32_t)indices.presentFamily, 0, &presentQueue);
}

void Vulkan::createSurface()
{
	VkResult	result;
	result = glfwCreateWindowSurface(instance, window, nullptr, &surface);
	if (result != VK_SUCCESS)
		throw arcade::GraphicsLibraryError("Unable to create Vulkan surface");
}

VkSurfaceFormatKHR Vulkan::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR> &availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return {VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR};
	}
	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}

VkPresentModeKHR Vulkan::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;

	for (const auto& availablePresentMode : availablePresentModes) {
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availablePresentMode;
		} else if (availablePresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availablePresentMode;
		}
	}
	return bestMode;
}

VkExtent2D Vulkan::chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities)
{
	VkExtent2D actualExtent = {(uint32_t)width, (uint32_t)height};

	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
	actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));
	return actualExtent;
}