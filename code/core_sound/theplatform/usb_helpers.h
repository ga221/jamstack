

#ifndef __USB_MISC_H__
#define __USB_MISC_H__

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define USB_BIG_ENDIAN (0U)

#define USB_LITTLE_ENDIAN (1U)

#ifndef ENDIANNESS
#define ENDIANNESS USB_LITTLE_ENDIAN
#endif

#if(defined(USE_RTOS) && (USE_RTOS > 0))
#define USB_OSA_WAIT_TIMEOUT (osaWaitForever_c)
#else
#define USB_OSA_WAIT_TIMEOUT (0U)
#endif

#if defined(__cplusplus)
extern "C"
{
#endif

  extern int DbgConsole_Printf(const char *fmt_s, ...);

#if defined(__cplusplus)
}
#endif

#ifndef __DSC__
#if defined(SDK_DEBUGCONSOLE) && (SDK_DEBUGCONSOLE < 1)
#define usb_echo printf
#else
#define usb_echo DbgConsole_Printf
#endif
#else
#define usb_echo
#endif

#if defined(__ICCARM__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED __packed
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED
#endif

#elif defined(__GNUC__)

#ifndef STRUCT_PACKED
#define STRUCT_PACKED
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED __attribute__((__packed__))
#endif

#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION))

#ifndef STRUCT_PACKED
#define STRUCT_PACKED _Pragma("pack(1U)")
#endif

#ifndef STRUCT_UNPACKED
#define STRUCT_UNPACKED _Pragma("pack()")
#endif

#endif

#define USB_SHORT_GET_LOW(x)  (((uint16_t)x) & 0xFFU)
#define USB_SHORT_GET_HIGH(x) ((uint8_t)(((uint16_t)x) >> 8U) & 0xFFU)

#define USB_LONG_GET_BYTE0(x) ((uint8_t)(((uint32_t)(x))) & 0xFFU)
#define USB_LONG_GET_BYTE1(x) ((uint8_t)(((uint32_t)(x)) >> 8U) & 0xFFU)
#define USB_LONG_GET_BYTE2(x) ((uint8_t)(((uint32_t)(x)) >> 16U) & 0xFFU)
#define USB_LONG_GET_BYTE3(x) ((uint8_t)(((uint32_t)(x)) >> 24U) & 0xFFU)

#define USB_MEM4_ALIGN_MASK (0x03U)

#define USB_MEM4_ALIGN(n)  ((n + 3U) & (0xFFFFFFFCu))
#define USB_MEM32_ALIGN(n) ((n + 31U) & (0xFFFFFFE0u))
#define USB_MEM64_ALIGN(n) ((n + 63U) & (0xFFFFFFC0u))

#define SWAP2BYTE_CONST(n) ((((n)&0x00FFU) << 8U) | (((n)&0xFF00U) >> 8U))
#define SWAP4BYTE_CONST(n) \
  ((((n)&0x000000FFU) << 24U) | (((n)&0x0000FF00U) << 8U) | (((n)&0x00FF0000U) >> 8U) | (((n)&0xFF000000U) >> 24U))

#define USB_ASSIGN_VALUE_ADDRESS_LONG_BY_BYTE(n, m)  \
  {                                                  \
    *((uint8_t *)&(n))     = *((uint8_t *)&(m));     \
    *((uint8_t *)&(n) + 1) = *((uint8_t *)&(m) + 1); \
    *((uint8_t *)&(n) + 2) = *((uint8_t *)&(m) + 2); \
    *((uint8_t *)&(n) + 3) = *((uint8_t *)&(m) + 3); \
  }

#define USB_ASSIGN_VALUE_ADDRESS_SHORT_BY_BYTE(n, m) \
  {                                                  \
    *((uint8_t *)&(n))     = *((uint8_t *)&(m));     \
    *((uint8_t *)&(n) + 1) = *((uint8_t *)&(m) + 1); \
  }

#define USB_ASSIGN_MACRO_VALUE_ADDRESS_LONG_BY_BYTE(n, m) \
  {                                                       \
    *((uint8_t *)&(n))     = (uint8_t)m;                  \
    *((uint8_t *)&(n) + 1) = (uint8_t)(m >> 8);           \
    *((uint8_t *)&(n) + 2) = (uint8_t)(m >> 16);          \
    *((uint8_t *)&(n) + 3) = (uint8_t)(m >> 24);          \
  }

#define USB_ASSIGN_MACRO_VALUE_ADDRESS_SHORT_BY_BYTE(n, m) \
  {                                                        \
    *((uint8_t *)&(n))     = (uint8_t)m;                   \
    *((uint8_t *)&(n) + 1) = (uint8_t)(m >> 8);            \
  }

#if(ENDIANNESS == USB_BIG_ENDIAN)

#define USB_SHORT_TO_LITTLE_ENDIAN(n)   SWAP2BYTE_CONST(n)
#define USB_LONG_TO_LITTLE_ENDIAN(n)    SWAP4BYTE_CONST(n)
#define USB_SHORT_FROM_LITTLE_ENDIAN(n) SWAP2BYTE_CONST(n)
#define USB_LONG_FROM_LITTLE_ENDIAN(n)  SWAP2BYTE_CONST(n)

#define USB_SHORT_TO_BIG_ENDIAN(n)   (n)
#define USB_LONG_TO_BIG_ENDIAN(n)    (n)
#define USB_SHORT_FROM_BIG_ENDIAN(n) (n)
#define USB_LONG_FROM_BIG_ENDIAN(n)  (n)

#define USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
  {                                             \
    m[3] = ((((uint32_t)(n)) >> 24U) & 0xFFU);  \
    m[2] = ((((uint32_t)(n)) >> 16U) & 0xFFU);  \
    m[1] = ((((uint32_t)(n)) >> 8U) & 0xFFU);   \
    m[0] = (((uint32_t)(n)) & 0xFFU);           \
  }

#define USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n) \
  ((uint32_t)((((uint8_t)n[3]) << 24U) | (((uint8_t)n[2]) << 16U) | (((uint8_t)n[1]) << 8U) | (((uint8_t)n[0]) << 0U)))

#define USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)   \
  {                                            \
    m[0] = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
    m[1] = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
    m[2] = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
    m[3] = (((uint32_t)(n)) & 0xFFU);          \
  }

#define USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n) \
  ((uint32_t)((((uint8_t)n[0]) << 24U) | (((uint8_t)n[1]) << 16U) | (((uint8_t)n[2]) << 8U) | (((uint8_t)n[3]) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
  {                                              \
    m[1] = ((((uint16_t)(n)) >> 8U) & 0xFFU);    \
    m[0] = (((uint16_t)(n)) & 0xFFU);            \
  }

#define USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n) ((uint32_t)((((uint8_t)n[1]) << 8U) | (((uint8_t)n[0]) << 0U)))

#define USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m) \
  {                                           \
    m[0] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
    m[1] = (((uint16_t)(n)) & 0xFFU);         \
  }

#define USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n) ((uint32_t)((((uint8_t)n[0]) << 8U) | (((uint8_t)n[1]) << 0U)))

#define USB_LONG_TO_LITTLE_ENDIAN_DATA(n, m)                     \
  {                                                              \
    *((uint8_t *)&(m) + 3) = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
    *((uint8_t *)&(m) + 2) = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
    *((uint8_t *)&(m) + 1) = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
    *((uint8_t *)&(m) + 0) = (((uint32_t)(n)) & 0xFFU);          \
  }

#define USB_LONG_FROM_LITTLE_ENDIAN_DATA(n)                                                                            \
  ((uint32_t)(((*((uint8_t *)&(n) + 3)) << 24U) | ((*((uint8_t *)&(n) + 2)) << 16U) | ((*((uint8_t *)&(n) + 1)) << 8U) \
              | ((*((uint8_t *)&(n))) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_DATA(n, m)                   \
  {                                                             \
    *((uint8_t *)&(m) + 1) = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
    *((uint8_t *)&(m))     = ((((uint16_t)(n))) & 0xFFU);       \
  }

#define USB_SHORT_FROM_LITTLE_ENDIAN_DATA(n) ((uint32_t)(((*((uint8_t *)&(n) + 1)) << 8U) | ((*((uint8_t *)&(n))))))

#else

#define USB_SHORT_TO_LITTLE_ENDIAN(n)   (n)
#define USB_LONG_TO_LITTLE_ENDIAN(n)    (n)
#define USB_SHORT_FROM_LITTLE_ENDIAN(n) (n)
#define USB_LONG_FROM_LITTLE_ENDIAN(n)  (n)

#define USB_SHORT_TO_BIG_ENDIAN(n)   SWAP2BYTE_CONST(n)
#define USB_LONG_TO_BIG_ENDIAN(n)    SWAP4BYTE_CONST(n)
#define USB_SHORT_FROM_BIG_ENDIAN(n) SWAP2BYTE_CONST(n)
#define USB_LONG_FROM_BIG_ENDIAN(n)  SWAP4BYTE_CONST(n)

#define USB_LONG_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
  {                                             \
    m[3] = ((((uint32_t)(n)) >> 24U) & 0xFFU);  \
    m[2] = ((((uint32_t)(n)) >> 16U) & 0xFFU);  \
    m[1] = ((((uint32_t)(n)) >> 8U) & 0xFFU);   \
    m[0] = (((uint32_t)(n)) & 0xFFU);           \
  }

#define USB_LONG_FROM_LITTLE_ENDIAN_ADDRESS(n) \
  ((uint32_t)((((uint8_t)n[3]) << 24U) | (((uint8_t)n[2]) << 16U) | (((uint8_t)n[1]) << 8U) | (((uint8_t)n[0]) << 0U)))

#define USB_LONG_TO_BIG_ENDIAN_ADDRESS(n, m)   \
  {                                            \
    m[0] = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
    m[1] = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
    m[2] = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
    m[3] = (((uint32_t)(n)) & 0xFFU);          \
  }

#define USB_LONG_FROM_BIG_ENDIAN_ADDRESS(n) \
  ((uint32_t)((((uint8_t)n[0]) << 24U) | (((uint8_t)n[1]) << 16U) | (((uint8_t)n[2]) << 8U) | (((uint8_t)n[3]) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_ADDRESS(n, m) \
  {                                              \
    m[1] = ((((uint16_t)(n)) >> 8U) & 0xFFU);    \
    m[0] = (((uint16_t)(n)) & 0xFFU);            \
  }

#define USB_SHORT_FROM_LITTLE_ENDIAN_ADDRESS(n) ((uint32_t)((((uint8_t)n[1]) << 8U) | (((uint8_t)n[0]) << 0U)))

#define USB_SHORT_TO_BIG_ENDIAN_ADDRESS(n, m) \
  {                                           \
    m[0] = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
    m[1] = (((uint16_t)(n)) & 0xFFU);         \
  }

#define USB_SHORT_FROM_BIG_ENDIAN_ADDRESS(n) ((uint32_t)((((uint8_t)n[0]) << 8U) | (((uint8_t)n[1]) << 0U)))

#define USB_LONG_TO_LITTLE_ENDIAN_DATA(n, m)                     \
  {                                                              \
    *((uint8_t *)&(m) + 3) = ((((uint32_t)(n)) >> 24U) & 0xFFU); \
    *((uint8_t *)&(m) + 2) = ((((uint32_t)(n)) >> 16U) & 0xFFU); \
    *((uint8_t *)&(m) + 1) = ((((uint32_t)(n)) >> 8U) & 0xFFU);  \
    *((uint8_t *)&(m) + 0) = (((uint32_t)(n)) & 0xFFU);          \
  }

#define USB_LONG_FROM_LITTLE_ENDIAN_DATA(n)                                                                            \
  ((uint32_t)(((*((uint8_t *)&(n) + 3)) << 24U) | ((*((uint8_t *)&(n) + 2)) << 16U) | ((*((uint8_t *)&(n) + 1)) << 8U) \
              | ((*((uint8_t *)&(n))) << 0U)))

#define USB_SHORT_TO_LITTLE_ENDIAN_DATA(n, m)                   \
  {                                                             \
    *((uint8_t *)&(m) + 1) = ((((uint16_t)(n)) >> 8U) & 0xFFU); \
    *((uint8_t *)&(m))     = ((((uint16_t)(n))) & 0xFFU);       \
  }

#define USB_SHORT_FROM_LITTLE_ENDIAN_DATA(n) ((uint32_t)(((*((uint8_t *)&(n) + 1)) << 8U) | ((*((uint8_t *)&(n))))))

#endif

#define USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL 1
#define USB_STACK_DEDICATED_RAM_TYPE_BDT        2

#if defined(__ICCARM__)

#define USB_WEAK_VAR __attribute__((weak))
#define USB_WEAK_FUN __attribute__((weak))

_Pragma("diag_suppress=Pm120")
#define USB_ALIGN_PRAGMA(x) _Pragma(#x)
    _Pragma("diag_default=Pm120")

#define USB_RAM_ADDRESS_ALIGNMENT(n) USB_ALIGN_PRAGMA(data_alignment = n)
        _Pragma("diag_suppress=Pm120")
#define USB_LINK_SECTION_PART(str)  _Pragma(#str)
#define USB_LINK_DMA_INIT_DATA(sec) USB_LINK_SECTION_PART(location = #sec)
#define USB_LINK_USB_GLOBAL         _Pragma("location = \"m_usb_global\"")
#define USB_LINK_USB_BDT            _Pragma("location = \"m_usb_bdt\"")
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
            _Pragma("diag_default=Pm120")
#define USB_LINK_DMA_NONINIT_DATA      _Pragma("location = \"m_usb_dma_noninit_data\"")
#define USB_LINK_NONCACHE_NONINIT_DATA _Pragma("location = \"NonCacheable\"")
#elif defined(__CC_ARM) || (defined(__ARMCC_VERSION))

#define USB_WEAK_VAR                 __attribute__((weak))
#define USB_WEAK_FUN                 __attribute__((weak))
#define USB_RAM_ADDRESS_ALIGNMENT(n) __attribute__((aligned(n)))
#define USB_LINK_DMA_INIT_DATA(sec)  __attribute__((section(#sec)))
#if defined(__CC_ARM)
#define USB_LINK_USB_GLOBAL __attribute__((section("m_usb_global"))) __attribute__((zero_init))
#else
#define USB_LINK_USB_GLOBAL __attribute__((section(".bss.m_usb_global")))
#endif
#if defined(__CC_ARM)
#define USB_LINK_USB_BDT __attribute__((section("m_usb_bdt"))) __attribute__((zero_init))
#else
#define USB_LINK_USB_BDT __attribute__((section(".bss.m_usb_bdt")))
#endif
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
#if defined(__CC_ARM)
#define USB_LINK_DMA_NONINIT_DATA __attribute__((section("m_usb_dma_noninit_data"))) __attribute__((zero_init))
#else
#define USB_LINK_DMA_NONINIT_DATA __attribute__((section(".bss.m_usb_dma_noninit_data")))
#endif
#if defined(__CC_ARM)
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section("NonCacheable"))) __attribute__((zero_init))
#else
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section(".bss.NonCacheable")))
#endif

#elif defined(__GNUC__)

#define USB_WEAK_VAR                 __attribute__((weak))
#define USB_WEAK_FUN                 __attribute__((weak))
#define USB_RAM_ADDRESS_ALIGNMENT(n) __attribute__((aligned(n)))
#define USB_LINK_DMA_INIT_DATA(sec)  __attribute__((section(#sec)))
#define USB_LINK_USB_GLOBAL          __attribute__((section("m_usb_global, \"aw\", %nobits @")))
#define USB_LINK_USB_BDT             __attribute__((section("m_usb_bdt, \"aw\", %nobits @")))
#define USB_LINK_USB_GLOBAL_BSS
#define USB_LINK_USB_BDT_BSS
#define USB_LINK_DMA_NONINIT_DATA      __attribute__((section("m_usb_dma_noninit_data, \"aw\", %nobits @")))
#define USB_LINK_NONCACHE_NONINIT_DATA __attribute__((section("NonCacheable, \"aw\", %nobits @")))

#elif defined(__DSC__)
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define USB_RAM_ADDRESS_ALIGNMENT(n)
#define USB_LINK_USB_BDT_BSS
#define USB_LINK_USB_GLOBAL_BSS
#else
#error The tool-chain is not supported.
#endif

#if(defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) \
    || (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))

#if((defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE)) && (defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)))
#define USB_CACHE_LINESIZE MAX(FSL_FEATURE_L2CACHE_LINESIZE_BYTE, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#elif(defined(FSL_FEATURE_L2CACHE_LINESIZE_BYTE))
#define USB_CACHE_LINESIZE MAX(FSL_FEATURE_L2CACHE_LINESIZE_BYTE, 0)
#elif(defined(FSL_FEATURE_L1DCACHE_LINESIZE_BYTE))
#define USB_CACHE_LINESIZE MAX(0, FSL_FEATURE_L1DCACHE_LINESIZE_BYTE)
#else
#define USB_CACHE_LINESIZE 4
#endif

#else
#define USB_CACHE_LINESIZE 4
#endif

#if(((defined(USB_DEVICE_CONFIG_LPCIP3511FS)) && (USB_DEVICE_CONFIG_LPCIP3511FS > 0U)) \
    || ((defined(USB_DEVICE_CONFIG_LPCIP3511HS)) && (USB_DEVICE_CONFIG_LPCIP3511HS > 0U)))
#define USB_DATA_ALIGN 64
#else
#define USB_DATA_ALIGN 4
#endif

#define USB_DATA_ALIGN_SIZE MAX(USB_CACHE_LINESIZE, USB_DATA_ALIGN)

#define USB_DATA_ALIGN_SIZE_MULTIPLE(n) ((n + USB_DATA_ALIGN_SIZE - 1U) & (~(USB_DATA_ALIGN_SIZE - 1U)))

#if defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM == USB_STACK_DEDICATED_RAM_TYPE_BDT_GLOBAL)

#define USB_GLOBAL USB_LINK_USB_GLOBAL
#define USB_BDT    USB_LINK_USB_BDT

#if(defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) \
    || (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(m_usb_dma_init_data)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#if(defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA USB_LINK_USB_GLOBAL
#endif
#endif

#elif defined(USB_STACK_USE_DEDICATED_RAM) && (USB_STACK_USE_DEDICATED_RAM == USB_STACK_DEDICATED_RAM_TYPE_BDT)

#define USB_BDT USB_LINK_USB_BDT

#if(defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) \
    || (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_GLOBAL               USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(m_usb_dma_init_data)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#if(defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_GLOBAL               USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_GLOBAL USB_LINK_USB_GLOBAL_BSS
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA
#endif
#endif

#else

#if(defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) \
    || (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))

#define USB_GLOBAL               USB_LINK_DMA_NONINIT_DATA
#define USB_BDT                  USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_DMA_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(m_usb_dma_init_data)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA

#else

#if(defined(DATA_SECTION_IS_CACHEABLE) && (DATA_SECTION_IS_CACHEABLE))
#define USB_GLOBAL               USB_LINK_NONCACHE_NONINIT_DATA
#define USB_BDT                  USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_NONINIT_SUB USB_LINK_NONCACHE_NONINIT_DATA
#define USB_DMA_DATA_INIT_SUB    USB_LINK_DMA_INIT_DATA(NonCacheable.init)
#define USB_CONTROLLER_DATA      USB_LINK_NONCACHE_NONINIT_DATA
#else
#define USB_GLOBAL USB_LINK_USB_GLOBAL_BSS
#define USB_BDT    USB_LINK_USB_BDT_BSS
#define USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_DATA_INIT_SUB
#define USB_CONTROLLER_DATA
#endif

#endif

#endif

#define USB_DMA_NONINIT_DATA_ALIGN(n) USB_RAM_ADDRESS_ALIGNMENT(n) USB_DMA_DATA_NONINIT_SUB
#define USB_DMA_INIT_DATA_ALIGN(n)    USB_RAM_ADDRESS_ALIGNMENT(n) USB_DMA_DATA_INIT_SUB

#if(defined(USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_DEVICE_CONFIG_BUFFER_PROPERTY_CACHEABLE)) \
    || (defined(USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE) && (USB_HOST_CONFIG_BUFFER_PROPERTY_CACHEABLE))
#define USB_DMA_DATA_NONCACHEABLE USB_LINK_NONCACHE_NONINIT_DATA

#else
#define USB_DMA_DATA_NONCACHEABLE
#endif

#define USB_GLOBAL_DEDICATED_RAM USB_LINK_USB_GLOBAL

#endif
