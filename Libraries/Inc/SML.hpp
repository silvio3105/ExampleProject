/**
 * @file SML.hpp
 * @author silvio3105 (www.github.com/silvio3105)
 * @brief SML header file.
 * 
 * @copyright Copyright (c) 2023, silvio3105
 * 
 */

/*
Copyright (c) 2023, silvio3105 (www.github.com/silvio3105)

Access and use of this Project and its contents are granted free of charge to any Person.
The Person is allowed to copy, modify and use The Project and its contents only for non-commercial use.
Commercial use of this Project and its contents is prohibited.
Modifying this License and/or sublicensing is prohibited.

THE PROJECT AND ITS CONTENT ARE PROVIDED "AS IS" WITH ALL FAULTS AND WITHOUT EXPRESSED OR IMPLIED WARRANTY.
THE AUTHOR KEEPS ALL RIGHTS TO CHANGE OR REMOVE THE CONTENTS OF THIS PROJECT WITHOUT PREVIOUS NOTICE.
THE AUTHOR IS NOT RESPONSIBLE FOR DAMAGE OF ANY KIND OR LIABILITY CAUSED BY USING THE CONTENTS OF THIS PROJECT.

This License shall be included in all functional textual files.
*/

#ifndef _SML_H_
#define _SML_H_

// ----- INCLUDE FILES
#include            <stdint.h>
#include			<stdio.h>
#include			<stdarg.h>


/** \addtogroup SML
 * 
 * Custom library with miscellaneous functions. 
 * @{
*/

// ----- DEFINES
#define SML_VERSION				"v1.0rc1" /**< @brief Library version. */

#ifndef SML_COPY_TIMEOUT
#define SML_COPY_TIMEOUT		3200 /**< @brief Timeout in ms for non-blocking copy operations. */
#endif // SML_COPY_TIMEOUT

#ifndef SML_LOGGER_TIMEOUT
#define SML_LOGGER_TIMEOUT		3200 /**< @brief Timeout in ms for non-blocking logger operations. */
#endif // SML_LOGGER_TIMEOUT

/**
 * @brief Snippet for creating static print handler.
 *
 * @param _name Handler name. 
 */
#define SML_PRINT_HANDLER(_name) \
	static void _name(const char* buffer, const uint16_t len)

/**
 * @brief Snippet for creating static copy handler.
 * 
 * @param _name Handler name.
 */
#define SML_COPY_HANDLER(_name) \
	static SML::Return_t _name(const void* source, void* destination, const uint16_t len)


// MACRO FUNCTIONS
/**
 * @brief Calculate number of members in array.
 * 
 * @param _in Input array.
 */
#define __SML_ARRAY_LEN(_in) \
	(sizeof(_in) / sizeof(_in[0]))

/**
 * @brief Set \c _bit of \c _value to 1.
 * 
 * @param _value Input value.
 * @param _bit Bit number of \c _value to change to 1.
 */
#define __SML_BIT_SET(_value, _bit) \
	_value |= 1 << (_bit)

/**
 * @brief Set \c _bit of \c _value to 0. 
 * 
 * @param _value Input value.
 * @param _bit Bit number of \c _value to change to 0. 
 */
#define __SML_BIT_CLEAR(_value, _bit) \
	_value &= ~(1 << (_bit))

/**
 * @brief Toggle \c _bit in \c _value
 * 
 * @param _value Input value.
 * @param _bit Bit number of \c _value to toggle.
 */
#define __SML_BIT_TOGGLE(_value, _bit) \
	_value ^= 1 << (_bit)

/**
 * @brief Fetch bit \c _bit power in \c _value
 * 
 * @param _value Input value.
 * @param _bit Bit number in \c _value to fetch.
 */
#define __SML_BIT_POWER(_value, _bit) \
	(_value & (1 << (_bit)))

/**
 * @brief Fetch \c _bit from \c _value
 * 
 * @param _value Input value.
 * @param _bit Bit number of \c _value to fetch.
 * 
 * @note Function returns \c 0 or \c 1.
 */
#define __SML_BIT_GET(_value, _bit) \
	(_value & (1 << (_bit))) >> (_bit)

/**
 * @brief Convert seconds to miliseconds
 * 
 * @param _in Input value in seconds.
 */
#define __SML_S_2_MS(_in) \
	(_in * 1000)

/**
 * @brief Convert minutes to seconds.
 * 
 * @param _in Input value in minutes.
 */
#define __SML_MIN_2_S(_in) \
	(_in * 60)

/**
 * @brief Convert minutes to miliseconds.
 * 
 * @param _in Input value in minutes.
 */
#define __SML_MIN_2_MS(_in) \
	(__SML_S_2_MS(__SML_MIN_2_S(_in)))
	
/**
 * @brief Convert hours to minutes.
 * 
 * @param _in Input value in hours.
 */
#define __SML_H_2_MIN(_in) \
	(_in * 60)

/**
 * @brief Convert hours to seconds.
 * 
 * @param _in Input value in hours.
 */
#define __SML_H_2_S(_in) \
	(__SML_MIN_2_S(__SML_H_2_MIN(_in)))


// ----- DEBUG STUFF
#if defined(DEBUG) && defined(DEBUG_HANDLER) && !defined(DEBUG_LEVEL)
/**
 * @brief Debug level.
 * 
 * All levels above selected are also included.
 * 
 * Debug levels: 
 * 0 = Verbose
 * 1 = Info
 * 2 = Warnings
 * 3 = Errors
 */
#define DEBUG_LEVEL 			0
#warning "[SML] Debug level not selected! Forced to level 0(verbose)."
#endif // DEBUG && DEBUG_HANDLER


// C++ STUFF
#ifdef __cplusplus

// Define debug functions for SML copy
#if defined(DEBUG_SML_COPY) && defined(DEBUG) && defined(DEBUG_HANDLER)
	void DEBUG_HANDLER(const char* str, ...);

	#if DEBUG_LEVEL <= 3
		#define __SML_COPY_ERROR_LOG DEBUG_HANDLER
	#else
		#define __SML_COPY_ERROR_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 2
		#define __SML_COPY_WARNING_LOG DEBUG_HANDLER
	#else
		#define __SML_COPY_WARNING_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 1
		#define __SML_COPY_INFO_LOG DEBUG_HANDLER
	#else
		#define __SML_COPY_INFO_LOG(...)
	#endif
	#if DEBUG_LEVEL == 0
		#define __SML_COPY_VERBOSE_LOG DEBUG_HANDLER
	#else
		#define __SML_COPY_VERBOSE_LOG(...)
	#endif
#else 
	#define __SML_COPY_ERROR_LOG(...)
	#define __SML_COPY_WARNING_LOG(...)
	#define __SML_COPY_INFO_LOG(...)
	#define __SML_COPY_VERBOSE_LOG(...)
#endif

// Define debug functions for SML ring buffer
#if defined(DEBUG_SML_RC) && defined(DEBUG) && defined(DEBUG_HANDLER)
	void DEBUG_HANDLER(const char* str, ...);

	#if DEBUG_LEVEL <= 3
		#define __SML_RB_ERROR_LOG DEBUG_HANDLER
	#else
		#define __SML_RB_ERROR_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 2
		#define __SML_RB_WARNING_LOG DEBUG_HANDLER
	#else
		#define __SML_RB_WARNING_LOG(...)
	#endif
	#if DEBUG_LEVEL <= 1
		#define __SML_RB_INFO_LOG DEBUG_HANDLER
	#else
		#define __SML_RB_INFO_LOG(...)
	#endif
	#if DEBUG_LEVEL == 0
		#define __SML_RB_VERBOSE_LOG DEBUG_HANDLER
	#else
		#define __SML_RB_VERBOSE_LOG(...)
	#endif
#else 
	#define __SML_RB_ERROR_LOG(...)
	#define __SML_RB_WARNING_LOG(...)
	#define __SML_RB_INFO_LOG(...)
	#define __SML_RB_VERBOSE_LOG(...)
#endif


// ----- DEBUG STUFF
#if defined(DEBUG) && defined(DEBUG_HANDLER)

/**
 * @brief Code snippet for creating handler for printing debug log.
 * 
 * @param _name Name of the logger object to use for printing.
 */
#define __SML_DEBUG_HANDLER(_name) \
	void DEBUG_HANDLER(const char* str, ...) \
	{ \
		va_list args; \
		va_start(args, str); \
		_name.printf(str, args); \
		va_end(args); \
	}
#else
/**
 * @brief Code snippet for creating handler for printing debug log.
 * 
 * @param _name Name of the logger object to use for printing.
 */
#define __SML_DEBUG_HANDLER(_loggerObject)
#endif // DEBUG && DEBUG_HANDLER


// ----- NAMESPACES
/**
 * @brief Namespace for Simple Miscellaneous Library.
 * 
 */
namespace SML
{
	// DATA CLASS
	/**
	 * @brief Class representing data of \c T type with \c len size.
	 * 
	 * @tparam T Data type.
	 * 
	 * @warning Maximum data length is 2^16 - 1!
	 */
	template<typename T>
	class Data 
	{
		public:
		// CONSTRUCTORS & DECONSTRUCTORS
		/**
		 * @brief Constructor for \c Data object.
		 * 
		 * @return No return value.
		 */
		Data(void)
		{
			// Set to default values
			dataAddr = nullptr;
			length = 0;			
		}

		/**
		 * @brief Constructor for \c Data object with data and length.
		 * 
		 * @param data Pointer to data set.
		 * @param len Length of \c data
		 * @return No return value.
		 */
		Data(T* data, uint16_t len)
		{
			dataAddr = data;
			length = len;
		}

		/**
		 * @brief Deconstructor for \c Data object.
		 * 
		 * @return No return value.
		 */
		~Data(void)
		{
			// Set to default values
			dataAddr = nullptr;
			length = 0;			
		}

		// METHOD DEFINITIONS
		/**
		 * @brief Get address of the data.
		 * 
		 * @return Pointer to data.
		 */
		inline T* get(void) const
		{
			// Return data address
			return dataAddr;
		}

		/**
		 * @brief Set new data.
		 * 
		 * @param newData Pointer to new data.
		 * @param newLen Length of new data.
		 * @return No return value.
		 */
		inline void set(T* newData, uint16_t newLen)
		{
			// Set new data pointer and length
			dataAddr = newData;
			length = newLen;
		}

		/**
		 * @brief Get data length.
		 * 
		 * @return Data length.
		 */
		inline uint16_t len(void) const
		{
			// Return data length
			return length;
		}


		private:
		T* dataAddr; /**< Pointer to data. */
		uint16_t length; /**< Length of \ref dataAddr. */
	};

	// ENUMS
	/**
	 * @brief Enum class with generic return statuses.
	 * 
	 */
	enum class Return_t : uint8_t
	{
		Ok = 0, /**< @brief Enum value for OK return status. */
		Nok, /**< @brief Enum value for not OK return status. */
		Error, /**< @brief Enum value for error return status. */
		Timeout, /**< @brief Enum value for timeout return status. */
		Warning, /**< @brief Enum value for warning return status. */

		NA = 255 /**< @brief Enum value for unknown return status. */
	};

	/**
	 * @brief Enum class with generic binary statuses.
	 * 
	 */
	enum class State_t : uint8_t
	{
		Off = 0, /**< @brief Enum value for off status. */
		On = 1 /**< @brief Enum value for on status. */
	};

	/**
	 * @brief Enum class with generic answers.
	 * 
	 */
	enum class Answer_t : uint8_t
	{
		No = 0, /**< @brief Enum value for negative answer. */
		Yes /**< @brief Enum value for positive answer. */
	};

	/**
	 * @brief Enum class with generic actions.
	 * 
	 */
	enum class Action_t: uint8_t
	{
		Disable = 0, /**< @brief Enum value for disable action. */
		Enable, /**< @brief Enum value for enable action. */
		Toggle /**< @brief Enum value for toggle action. */
	};

	/**
	 * @brief Enum class with process types.
	 * 
	 */
	enum class Process_t : uint8_t
	{
		Blocking = 0, /**< @brief Enum value for blocking process. */
		NonBlocking = 1 /**< @brief Enum value for non blocking process. */
	};

	/**
	 * @brief Enum class with time formats.
	 * 
	 */
	enum class TimeFomrat_t : uint8_t
	{
		Time24H = 0, /**< @brief Enum value for 24h time format. */
		TimeAMPM /**< @brief Enum value for 12 hour AM-PM format. */
	};

	/**
	 * @brief Enum class with days.
	 * 
	 */
	enum class Day_t : uint8_t
	{
		Monday = 1,
		Tuesday = 2,
		Wednesday = 3,
		Thursday = 4,
		Friday = 5,
		Saturday = 6,
		Sunday = 7
	};

	/**
	 * @brief Enum class with months.
	 * 
	 */
	enum class Month_t : uint8_t
	{
		January = 1,
		February = 2,
		March = 3,
		April = 4,
		May = 5,
		June = 6,
		July = 7,
		August = 8,
		September = 9,
		October = 10,
		November = 11,
		December = 12
	};

	/**
	 * @brief Enum class with year types.
	 * 
	 */
	enum class Year_t : uint8_t
	{
		Normal = 0, /**< @brief Enum value for non-leap year type. */
		Leap /**< @brief Enum value for leap year type. */
	};

	/**
	 * @brief Enum class with semaphore statuses.
	 * 
	 */
	enum class Semaphore_t : uint8_t
	{
		Free = 0, /**< @brief Enum value for free semaphore. */
		Taken /**< @brief Enum value for taken semaphore. */
	};


	// TYPEDEFS
	/**
	 * @brief Definition for generic function without return.
	 * 
	 * @return No return value.
	 */
	typedef void (*ext_handler_f)(void);

	/**
	 * @brief Definition for generic function that returns \c uint32_t 
	 * 
	 * @return \c uint32_t value.
	 */
	typedef uint32_t (*ext_handler_u32_f)(void);

	/**
	 * @brief Definition for function for printing strings.
	 * 
	 * @param buffer Pointer to string to send.
	 * @param len Length of \c buffer
	 * @return No return value.
	 */
	typedef void (*print_handler_f)(const char* buffer, const uint16_t len);

	/**
	 * @brief Definition for function for handling copy operation.
	 * 
	 * @param source Pointer to address to copy from.
	 * @param destination Pointer to address to copy to.
	 * @param len Number of bytes to copy from \c source to \c destionation
	 * @return \c SML::Return_t::Nok if copy failed.
	 * @return \c SML::Return_t:Ok if copy is successful.
	 */
	typedef SML::Return_t (*copy_handler_f)(const void* source, void* destination, const uint16_t len);


	// STRUCTS
	/**
	 * @brief Struct for input info for \ref SML::parse function.
	 * 
	 */
	struct parser_t
	{
		char endSeparator; /**< End separator character. */
		uint8_t endSeparatorCnt; /**< Number of \ref endSeparator after \ref startSeparator is found. */
		char startSeparator; /**< Separator character before wanted parameter. */
		uint8_t startSeparatorCnt; /**< Number of \ref startSeparator before wanted parameter. */		
		SML::Data<char> output; /**< \c char type output data. */
	};


	// FUNCTION DECLARATIONS
	void fill(void* address, const uint8_t value, uint16_t len);
	void copy(const void* source, void* destination, uint16_t len);
	void swapEndian(void* output, const void* input, const uint8_t len);
	inline constexpr SML::Answer_t isDigit(const char ch);
	inline constexpr uint8_t char2Num(const char ch);
	inline constexpr SML::Answer_t isMinute(const uint8_t in);
	inline constexpr SML::Answer_t isSecond(const uint8_t in);
	constexpr SML::Answer_t isHour(const uint8_t in, const SML::TimeFomrat_t format = SML::TimeFomrat_t::Time24H);
	inline constexpr SML::Year_t getYearType(const uint16_t year);
	SML::Answer_t isDateValid(const uint8_t day, const uint8_t month, const uint16_t year);
	constexpr inline float abs(float in);
	inline constexpr uint8_t dec2BCD(const uint8_t in);
	inline constexpr uint8_t bcd2Dec(const uint8_t in);
	char* tok(char* input, const char separator);
	uint16_t len(const char* input, const char endChar = '\0');
	uint16_t count(const char* input, const char character, const char endChar = '\0');
	SML::Return_t cmp(const char* input1, const char* input2, char endChar = '\0');
	char* findToken(const char* input, const char sep, char sepCnt, const SML::Answer_t retNull);	
	SML::Return_t parse(char* input, char startSeparator, uint8_t startSeparatorCnt, char endSeparator, uint8_t endSeparatorCnt, SML::Data<char>& output, const SML::Answer_t modify = SML::Answer_t::No);
	uint8_t parse(char* input, SML::parser_t* list, const uint8_t len, const SML::Answer_t modify = SML::Answer_t::No, const SML::Answer_t sorted = SML::Answer_t::No);


	#ifdef SML_IMPLEMENTATION

	// FUNCTION DEFNITIONS
	/**
	 * @brief Fill \c len bytes from \c address with \c value
	 * 
	 * @param address Pointer to start address to fill with \c value
	 * @param value Value to fill with.
	 * @param len Lenght in bytes to fill.
	 * @return No return value.
	 */
	void fill(void* address, const uint8_t value, uint16_t len)
	{
		len--;

		while (len--) 
		{
			((uint8_t*)address)[len] = value;
		}
	}

	/**
	 * @brief Copy \c len bytes from \c source to \c destination
	 * 
	 * @param source Pointer to address to copy from.
	 * @param destination Pointer to address to copy to.
	 * @param len Number of bytes to copy from \c source to \c destionation
	 * @return No return value.
	 */
	void copy(const void* source, void* destination, uint16_t len)
	{
		len--;

		while (len--)
		{
			((uint8_t*)destination)[len] = ((uint8_t*)source)[len];
		}
	}

	/**
	 * @brief Swap endian.
	 * 
	 * Eg., convert data 0x11223344 to 0x44332211.
	 * 
	 * @param output Pointer to output variable.
	 * @param input Pointer to input variable.
	 * @param len Length of \c input variable in bytes.
	 * @return No return value. 
	 */
	void swapEndian(void* output, const void* input, const uint8_t len)
	{
		for (uint8_t i = 0; i < len; i++)
		{
			((uint8_t*)output)[i] = ((uint8_t*)input)[(len - 1) - i];
		}
	}


	/**
	 * @brief Check if character is digit.
	 * 
	 * @param ch Input character.
	 * @return \c SML::Answer_t::No if \c ch is not digit.
	 * @return \c SML::Answer_t::Yes if \c ch is digit.
	 */
	inline constexpr SML::Answer_t isDigit(const char ch)
	{
		if (ch >= '0' && ch <= '9')
		{
			return SML::Answer_t::Yes;
		}

		return SML::Answer_t::No;
	}

	/**
	 * @brief Convert character to number.
	 * 
	 * @param ch Input character.
	 * @return Character converted to number.
	 * 
	 * @warning Function does not checks if input character is number. Use \ref isDigit function to check if character is number.
	 */
	inline constexpr uint8_t char2Num(const char ch)
	{
		return (ch - '0');
	}

	/**
	 * @brief Validate input value as minute.
	 * 
	 * @param in Input value.
	 * @return \c SML::Answer_t::No if value \c in is not minute.
	 * @return \c SML::Answer_t::Yes if value \c in is minute.
	 */
	inline constexpr SML::Answer_t isMinute(const uint8_t in)
	{
		if (in >= 0 && in < 60)
		{
			return SML::Answer_t::Yes;
		}

		return SML::Answer_t::No; 				
	}

	/**
	 * @brief Validate input value as second.
	 * 
	 * @param in Input value.
	 * @return \c SML::Answer_t::No if value \c in is not second.
	 * @return \c SML::Answer_t::Yes if value \c in is second.
	 * 
	 * @note Leap second is not supported.
	 */
	inline constexpr SML::Answer_t isSecond(const uint8_t in)
	{
		return SML::isMinute(in);
	}

	/**
	 * @brief Validate input value for hours.
	 * 
	 * @param in Input value.
	 * @param format Hour format. See \ref SML::TimeFomrat_t
	 * @return \c SML::Answer_t::No if input value \c in is not not hour.
	 * @return \c SML::Answer_t::Yes if input value \c in is hour.
	 */
	constexpr SML::Answer_t isHour(const uint8_t in, const SML::TimeFomrat_t format)
	{
		if (format == SML::TimeFomrat_t::Time24H && in >= 0 && in < 24)
		{
			return SML::Answer_t::Yes;
		}
		else if (format == SML::TimeFomrat_t::TimeAMPM && in > 0 && in < 13)
		{
			return SML::Answer_t::Yes;
		}

		return SML::Answer_t::No;
	}

	/**
	 * @brief Get year type.
	 * 
	 * @param year Input year.
	 * @return \c SML::Year_t::Normal for non-leap year.
	 * @return \c SML::Year_t::Leap for leap year.
	 */
	inline constexpr SML::Year_t getYearType(const uint16_t year)
	{
		if (year % 4)
		{
			return SML::Year_t::Normal;
		}

		return SML::Year_t::Leap;		
	}

	/**
	 * @brief Validate date.
	 * 
	 * @param day Input day.
	 * @param month Input month.
	 * @param year Input year.
	 * @return \c SML::Answer_t::No if date is not valid.
	 * @return \c SML::Answer_t::Yes if date is valid.
	 */
	SML::Answer_t isDateValid(const uint8_t day, const uint8_t month, const uint16_t year)
	{
		// Validate year
		if (year < 1900 || year > 2100)
		{
			return SML::Answer_t::No;
		}

		// Validate day
		if (day > 31)
		{
			return SML::Answer_t::No;
		}

		// Validate month and day
		switch (month)
		{
			case 2:
			{
				if (SML::getYearType(year) == SML::Year_t::Leap)
				{
					if (day > 29)
					{
						return SML::Answer_t::No;
					}
				}
				else if (day > 28)
				{
					return SML::Answer_t::No;
				}

				break;
			}

			case 4:
			case 6:
			case 9:
			case 11:
			{
				if (day > 30)
				{
					return SML::Answer_t::No;
				}

				break;
			}

			default:
			{
				return SML::Answer_t::No;
			}
		}

		return SML::Answer_t::Yes;		
	}

	/**
	 * @brief Scale input value to desired output value range.
	 * 
	 * @tparam T Data type.
	 * @param in Input value.
	 * @param inMin Input minimum value.
	 * @param inMax Input maximum value.
	 * @param outMin Output minimum value.
	 * @param outMax Output maximum value.
	 * @return \c in value scaled to fit range defined with \c outMin and \c outMax
	 */	
	template<typename T>
	constexpr T scale(T in, T inMin, T inMax, T outMin, T outMax)
	{
		return (in - inMin) * (outMax - outMin) / (inMax - inMin) + outMin;		
	}

	/**
	 * @brief Find lowest value between 2 input values.
	 * 
	 * @tparam T Data type.
	 * @param in1 Input value 1.
	 * @param in2 Input value 2.
	 * @return Lowest value between \c in1 and \c in2
	 */
	template<typename T>
	constexpr inline T min(T in1, T in2)
	{
		return (in1 < in2) ? in1 : in2;
	}

	/**
	 * @brief Find greatest value between 2 input values.
	 * 
	 * @tparam T Data type.
	 * @param in1 Input value 1.
	 * @param in2 Input value 2.
	 * @return Greatest value between \c in1 and \c in2
	 */	
	template<typename T>
	constexpr inline T max(T in1, T in2)
	{
		return (in1 > in2) ? in1 : in2;
	}

	/**
	 * @brief Find lowest value between 3 input values.
	 * 
	 * @tparam T Data type.
	 * @param in1 Input value 1.
	 * @param in2 Input value 2.
	 * @param in3 Input value 3.
	 * @return Lowest value between \c in1 \c in2 and \c in3
	 */	
	template<typename T>		
	constexpr T min(T in1, T in2, T in3)
	{
		return (in1 < in2) ? (in1 < in3 ? in1 : in3) : (in2 < in3 ? in2 : in3);
	}

	/**
	 * @brief Find greatest value between 3 input values.
	 * 
	 * @tparam T Data type.
	 * @param in1 Input value 1.
	 * @param in2 Input value 2.
	 * @param in3 Input value 3.
	 * @return Greatest value between \c in1 \c in2 and \c in3
	 */	
	template<typename T>	
	constexpr T max(T in1, T in2, T in3)
	{
		return (in1 > in2) ? (in1 > in3 ? in1 : in3) : (in2 > in3 ? in2 : in3);
	}

	/**
	 * @brief Return absolute value.
	 * 
	 * @tparam T Data type.
	 * @param in Input value.
	 * @return Absolute value from \c in value.
	 */
	template<typename T>
	constexpr inline T abs(T in)
	{
		return (in < 0) ? in * (-1) : in;
	}

	/**
	 * @brief Return float absolute value.
	 * 
	 * @param in Input float value.
	 * @return Absolute value from \c in value.
	 */
	constexpr inline float abs(float in)
	{
		return (in < 0) ? in * (-1.00f) : in;
	}

	/**
	 * @brief Limit/constrain value \c in between \c low and \c high
	 * 
	 * @tparam T Data type.
	 * @param in Input value.
	 * @param low Low limit value.
	 * @param high High limit value.
	 * @return \c in value if it is between \c low and \c high
	 * @return \c min value if \c in is smaller than \c min
	 * @return \c max value if \c in is greater than \c max
	 * @return Return limited value.
	 */
	template<typename T>
	constexpr inline T limit(T in, T low, T high)
	{
		return ((in < low) ? low : ((in > high) ? high : in));
	}

	/**
	 * @brief Sum all integer digits.
	 * 
	 * Example: Number 123456 will result with 21(1 + 2 + 3 + 4 + 5 + 6).
	 * 
	 * @param input Input number.
	 * @return Sum of all digits.
	 */
	template<typename T>
	uint8_t sumDigits(T input)
	{
		uint8_t sum = 0;

		// Remove - sign if needed
		input = abs<T>(input);

		// Do while input is not zero
		do
		{
			// Increase sum with digit
			sum += input % 10;

			// Remove digit from input integer
			input /= 10;
		}
		while (input);
		
		// Return sum of all digits
		return sum;		
	}

	/**
	 * @brief Convert 8-bit decimal value to BCD.
	 * 
	 * Example: 22 in decimal will become 0x22 in hex.
	 * 
	 * @param in Input 8-bit value.
	 * @return Value \c num in BCD.
	 */
	inline constexpr uint8_t dec2BCD(const uint8_t in)
	{
		return ((in / 10) << 4) + (in % 10);

	}

	/**
	 * @brief Convert 8-bit BCD value to decimal.
	 * 
	 * Example: 0x22 in BCD will become 22 in decimal.
	 * 
	 * @param in Input 8-bit value.
	 * @return Value \c num in decimal.
	 */
	inline constexpr uint8_t bcd2Dec(const uint8_t in)
	{
		return ((in >> 4) * 10) + (in & 0x0F);
	}

	/**
	 * @brief Convert C-string to decimal value.
	 * 
	 * @tparam T Output data type, eg., \c uint8_t
	 * @param str Pointer to C-string.
	 * @param endChar End character of \c str string.
	 * @return C-string number converted to decimal.
	 */
	template<typename T>
	T str2Dec(const char* str, const char endChar)
	{
		T value = 0;
		uint8_t idx = 0;

		// Move to next char if first char is minus
		if (str[0] == '-')
		{
			idx++;
		}

		// While char is number and not equal to end char
		while (str[idx] != endChar && SML::isDigit(str[idx]) == SML::Answer_t::Yes)
		{
			// Add one digit to output value
			value *= 10;

			// Add converted char to output value 
			value += SML::char2Num(str[idx]);

			// Move index
			idx++;
		}

		// If first char is minus, convert output value to negative
		if (str[0] == '-')
		{
			value *= (-1);
		}

		return value;
	}

	/**
	 * @brief Replace desired character with NULL character.
	 * 
	 * Replaces \c separator in \c input C-string and returns address of next character if it is not NULL character.
	 * 
	 * @param input C-string input.
	 * @param separator Separator character
	 * @return \c nullptr if end of \c input C-string is reached.
	 * @return Pointer to next token in \c input C-string.
	 */
	char* tok(char* input, const char separator)
	{
		// Move pointer until separator is found or end of C-string is reached
		while (*input && *input != separator)
		{
			input++;
		}

		// If NULL character is found, return nullptr
		if (!(*input))
		{
			return nullptr;
		}

		// Place NULL char over separator
		*input = '\0';

		// Move pointer to next character
		input++;

		// Return nullptr if character is NULL overwise return address of character
		if (!(*input))
		{
			return nullptr;
		}
		
		return input;		
	}

	/**
	 * @brief Find length of input C-string.
	 * 
	 * @param input Pointer to C-string.
	 * @param endChar Character where function should stop. This parameter is optional.
	 * @return Length of C-string.
	 */
	uint16_t len(const char* input, const char endChar)
	{
		// Copy string address to local variable
		const char* tmp = input;

		// Move pointer until endChar is found
		while (*tmp++ != endChar);

		// Return length of string.
		return (tmp - 1) - input;
	}

	/**
	 * @brief Count number of \c character in \c input C-string.
	 * 
	 * @param input Pointer to C-string.
	 * @param character Character to count.
	 * @param endChar Character where function should stop. This parameter is optional.
	 * @return Number of \c character in \c input
	 */
	uint16_t count(const char* input, const char character, const char endChar)
	{
		uint16_t count = 0;

		// If selected character is not equal to end character
		while (*input != endChar)
		{
			// If selected character is equal to wanted character, increas counter
			if (*input++ == character)
			{
				count++;
			}
		}

		// Return number of character in input C-string
		return count;	
	}

	/**
	 * @brief Compare two C-strings.
	 * 
	 * @param input1 Pointer to first C-string.
	 * @param input2 Pointer to second C-string.
	 * @param endChar Character where function should stop. This parameter is optional.
	 * @return \c SML::Return_t::Nok if strings are not equal.
	 * @return \c SML::Return_t::Ok if strings are equal. 
	 */
	SML::Return_t cmp(const char* input1, const char* input2, char endChar)
	{
		// While both characters are not equal to endChar
		while (*input1 != endChar)
		{
			// Stop if characters are not equal
			if (*input1++ != *input2++)
			{
				return SML::Return_t::Nok;
			}
		}

		// Stop if strings do not end with same character. This is input C-string length check
		if (*input1 != *input2)
		{
			return SML::Return_t::Nok;
		}

		return SML::Return_t::Ok;		
	}

	/**
	 * @brief Find token in C-string.
	 * 
	 * @param input Pointer to input C-string.
	 * @param sep Seperator character.
	 * @param sepCnt Number of separators before end of token.
	 * @param retNull Set to \c SML::Answer_t::Yes to return \c nullptr if \c \0 character is found. Set to \c SML::Answer_t::No to return address if \c \0 is found.
	 * @return \c nullptr if no token was found.
	 * @return Address of last found separator.
	 */
	char* findToken(const char* input, const char sep, char sepCnt, const SML::Answer_t retNull)
	{
		// If character is not \0
		while (*input) 
		{
			// If wanted character is found
			if (*input == sep)
			{
				// If that is wanted separator
				if (!sepCnt)
				{
					return (char*)input;
				}
				else
				{
					sepCnt--;
				}
			}

			// Move to next character
			input++;		
		}

		// Return nullptr if retNull param is not 0, otherwise return address of character
		if (retNull == SML::Answer_t::Yes)
		{
			return nullptr;
		}
		
		return (char*)input;
	}

	// STRING PARSE FUNCTIONS DEFINITIONS
	/**
	 * @brief Generic C-string parser. 
	 * 
	 * This function is replacment for scanf function. C-string format must be known to use this function.
	 * Function returns \c SML::Return_t::Ok and result even if \c \0 is encountered during searching for token's end.
	 * Set \c \0 as start separator to indicate that wanted token starts from begining of input C-string.
	 * 
	 * Example #1:
	 * C-string \c test1-test2.hello,test123 and call \c parse(string,'.',0,'\0',0,output) -> output will be pointing at letter \c h and length will be 13. Output C-string will be \c hello,test123
	 * 
	 * Example #2:
	 * C-string \c test1,test2-test3-test4.test5,test6 and call \c parse(string,'-',1,',',0,output) -> output C-string will be \c test4.test5 length will be 11.
	 * \c 1 because there is \c 1 \c - before wanted token, dash between \c test2 and \c test3
	 * \c 0 because there is \c 0 \c , after \c sepBegin
	 * 
	 * Example #3:
	 * C-string \c test1,test2,test3-test4.test5,test6 and call \c parse(string,'\0',0,',',1,output) -> output C-string will be \c test1,test2 length will be 11.
	 * \c \0 as begin separator indicates that wanted token starts from begining. In that case, \c sepCntBegin parameter makes no effect.
	 * 
	 * See example code for more info.
	 * 
	 * @param input Pointer to first character in C-string.
	 * @param startSeparator Character used as separator before wanted token.
	 * @param startSeparatorCnt Number of separators before wanted token.
	 * @param endSeparator Character used as separator after wanted token.
	 * @param endSeparatorCnt Number of separators after wanted token is found.
	 * @param output Reference to char output data. 
	 * @param modify Set to \c SML::Answer_t::Yes to replace found separator with \c \0 char.
	 * @return \c SML::Return_t::Nok if no token was found.
	 * @return \c SML::Return_t::Ok if token was found.
	 * 
	 * @warning \c sepCntBegin and \c sepCntEnd start from 0!
	 * @note C-string has to be NULL terminated.
	 * @note Function parses from left to right.
	 */
	SML::Return_t parse(char* input, char startSeparator, uint8_t startSeparatorCnt, char endSeparator, uint8_t endSeparatorCnt, SML::Data<char>& output, const SML::Answer_t modify)
	{
		// If first character is NULL
		if (!(*input))
		{
			// Set data to nullptr and 0 length and return not OK status
			output.set(nullptr, 0);
			return SML::Return_t::Nok;		
		}

		char* start = nullptr;
		
		// Set start to first character if startSeparator param is NULL character
		if (startSeparator)
		{
			start = findToken(input, startSeparator, startSeparatorCnt, SML::Answer_t::Yes);
		}
		else
		{
			start = input;
		}

		// If start of the token was not found
		if (!start)
		{
			// Set data to nullptr and 0 length and return not OK status
			output.set(nullptr, 0);
			return SML::Return_t::Nok;
		}
		else if (start[1]) // If next character is not \0
		{
			// Move start to next character
			start++;
			
			// Set output data to start address and end - start length
			if (startSeparator)
			{
				output.set(start, findToken(start, endSeparator, endSeparatorCnt, SML::Answer_t::No) - start);
			}
			else
			{
				output.set(start - 1, findToken(start, endSeparator, endSeparatorCnt, SML::Answer_t::No) - start + 1); // -1 byte for start address and +1 to include first character
			}

			// Replace character with \0 char
			if (modify == SML::Answer_t::Yes)
			{
				output.get()[output.len()] = '\0';
			}

			return SML::Return_t::Ok;
		}

		return SML::Return_t::Nok;		
	}

	/**
	 * @brief Parse C-string for multiple data.
	 * 
	 * This function works same as \ref parse
	 * Only difference is this function parse multiple data.
	 * If output result is \c nullptr then wanted part was not found.
	 * See example code for more info.
	 * 
	 * @param input Pointer to first character in C-string.
	 * @param list Pointer to parser list.
	 * @param len Length of \c list
	 * @param modify Set to \c SML::Answer_t::Yes to replace found separator with \c \0 char.
	 * @param sorted Set to \c SML::Answer_t::Yes if \c input list is sorted(from left to right). Function will continue where it stopped during parse for previous entry in \c input list.
	 * @return Number of parsed data.
	 * 
	 * @warning \c modify can be used only when \c data list is \c sorted
	 * @note If \c data list is sorted, set param \c sorted to \c SML::Answer_t::Yes to make parsing faster.  
	 * @note C-string has to be NULL terminated.
	 * @note Function parses from left to right.
	 */
	uint8_t parse(char* input, SML::parser_t* list, const uint8_t len, const SML::Answer_t modify, const SML::Answer_t sorted)
	{
		uint8_t total = 0;

		// Loop through input list
		for (uint8_t i = 0; i < len; i++)
		{
			// Call single parse function.
			if (parse(input, sorted == SML::Answer_t::Yes ? '\0' : list[i].startSeparator, list[i].startSeparatorCnt, list[i].endSeparator, list[i].endSeparatorCnt, list[i].output, modify) == SML::Return_t::Ok)
			{
				total++;
			}

			// Calculate new start position if input list is sorted
			if (sorted == SML::Answer_t::Yes)
			{
				input += list[i].output.len() + 1;
			}
		}

		return total;		
	}

	#endif // SML_IMPLEMENTATION


	// CLASSES
	/**
	 * @brief Ring buffer class.
	 * 
	 * @tparam T Type of ring buffer data, eg., \c uint32_t
	 * @tparam N Number of \c T members in ring buffer.
	 */
	template<typename T, uint16_t N>
	class RingBuffer
	{
		public:
		// CONSTRUCTORS & DECONSTRUCTORS
		/**
		 * @brief Ring buffer constructor.
		 * 
		 * @return No return value.
		 */
		RingBuffer(void)
		{
			// Reset pointers
			head = 0;
			tail = 0;

			fill(data, 0, maxSize);
		}

		/**
		 * @brief Ring buffer deconstructor.
		 * 
		 * @return No return value.
		 */
		~RingBuffer(void)
		{
			// Reset pointers
			head = 0;
			tail = 0;		
		}

		// METHOD DEFINITIONS
		/**
		 * @brief Write single \c T type data to ring buffer.
		 * 
		 * @param input Data of \c T type to write.
		 * @return No return value.
		 */
		inline void write(T input)
		{
			// Write single data to ring buffer
			writeData(input);			
		}

		/**
		 * @brief Write multiple data to ring buffer.
		 * 
		 * @param input Pointer to data array of \c T type to write.
		 * @param len Length of \c data
		 * @return No return value.
		 */
		void write(T* input, uint16_t len)
		{
			// Write data to ring buffer
			for (uint16_t i = 0; i < len; i++)
			{
				writeData(input[i]);
			}	
		}

		/**
		 * @brief Read signle data from ring buffer.
		 * 
		 * @param output Reference for output of \c T type.
		 * @return Number of read bytes.
		 */
		uint16_t read(T& output)
		{
			// Abort if there's no data to read
			if (!used())
			{
				return 0;
			}

			// Store data in tmp variable
			output = data[tail];

			// Move tail
			move(tail, SML::Answer_t::No);

			// Return OK status
			return 1;			
		}

		/**
		 * @brief Read multiple data from ring buffer.
		 * 
		 * @param output Pointer to array for output data of \c T type. 
		 * @param len Length of \c output array.
		 * @return Number of read bytes.
		 */
		uint16_t read(T* output, uint16_t len)
		{
			// If there is no data to read
			if (!used())
			{
				return 0;
			}

			// Limit number of data to read
			if (len > used())
			{
				len = used();
			}

			// Read data from buffer
			for (uint16_t i = 0; i < len; i++)
			{
				// Fetch next data
				output[i] = data[tail];

				// Move tail
				move(tail, SML::Answer_t::No);
			}

			return len;		
		}

		/**
		 * @brief Flush all data from ring buffer.
		 * 
		 * @return No return value.
		 */
		void flush(void)
		{
			// Reset head and tail
			head = 0;
			tail = 0;

			// Set all bytes to \0 (NULL char)
			fill(data, 0, size() * sizeof(T));			
		}

		/**
		 * @brief Fetch number of used data in ring buffer.
		 * 
		 * @return Number of used data.
		 */
		inline uint16_t used(void) const
		{
			// Check if ring buffer is wrapped
			if (head < tail)
			{
				return size() - (tail - head);
			}

			return head - tail;		
		}

		/**
		 * @brief Fetch number of free data in ring buffer.
		 * 
		 * @return Number of free data.
		 */
		inline uint16_t free(void) const
		{
			// Return number of free data slots in ring buffer
			return (size() - used());			
		}

		/**
		 * @brief Is ring buffer full.
		 * 
		 * @return \c SML::Return_t::Nok if ring buffer is not full.
		 * @return \c SML::Return_t::Ok if ring buffer is full.
		 */
		inline SML::Return_t isFull(void) const
		{
			// Return OK status if ring buffer is full
			if (!free())
			{
				return SML::Return_t::Ok;
			}
			else
			{
				return SML::Return_t::Nok;
			}			
		}

		/**
		 * @brief Get ring buffer size.
		 * 
		 * @return Size of ring buffer.
		 */
		inline constexpr uint16_t size(void) const
		{
			// Return ring buffer size
			return maxSize;	
		}


		private:
		// VARIABLES
		T data[N]; /**< @brief Array of \c T type where ring buffer data will be stored. */
		const uint16_t maxSize = N; /**< @brief Size of \ref data array. */
		uint16_t head = 0; /**< @brief Head data index. */
		uint16_t tail = 0; /**< @brief Tail data index. */

		// METHOD DEFINITIONS
		/**
		 * @brief Write single \c T type data to ring buffer.
		 * 
		 * @param input Data of \c T type to write.
		 * @return No return value.
		 */
		void writeData(T input)
		{
			// Write data to head pointer
			data[head] = input;

			// Move head
			move(head, SML::Answer_t::Yes);
		}

		/**
		 * @brief move \c pointer by one data member.
		 * 
		 * @param pointer Reference to pointer to increase.
		 * @param overflow Check for overflow. See \ref SML::Answer_t
		 * @return No return value.
		 */
		void move(uint16_t& pointer, SML::Answer_t overflow)
		{
			// Move tail pointer
			pointer++;

			// Reset tail pointer
			if (pointer >= size())
			{
				pointer = 0;
			}

			// Move tail if overflow is detected
			if (overflow == SML::Answer_t::Yes && pointer == tail)
			{
				__SML_RB_WARNING_LOG("Ring buffer %08X overflow\n", this);
				move(tail, SML::Answer_t::No);
			}						
		}
	};	
	
	/**
	 * @brief Logger class.
	 * 
	 * Wrapper for logging process. Process can be blocking or non-blocking. User can easly switch from blocking to non-blocking process or switch from classic UART to Segger's RTT or custom trace log in non-inited SRAM via external handler.
	 * 
	 * In case of non-blocking process, user must "mark" print process done with \ref done method. 
	 * 
	 * @tparam N Buffer size in bytes for formatted prints.
	 */
	template<uint16_t N>
	class Logger
	{
		public:
		// CONSTRUCTOR AND DECONSTRUCTOR DECLARATIONS
		/**
		 * @brief Logger constructor for blocking logging process.
		 * 
		 * @param handler Pointer to external function for handling buffer transfer(printing).
		 * @param fix Prefix C-string. Has to be NULL terminated.
		 * @param initedState Logger initial state. See \ref SML::State_t
		 * @param mspInit Pointer to external function for MSP init.
		 * @param mspDeinit Pointer to external function for MSP deinit.
		 * @return No return value.
		 */
		Logger(SML::print_handler_f handler, const char* fix = "", SML::State_t initedState = SML::State_t::On, SML::ext_handler_f mspInit = nullptr, SML::ext_handler_f mspDeinit = nullptr)
		{
			printHandler = handler;
			mspDeinitHandler = mspDeinit;
			prefix = fix;
			prefixLen = SML::len(fix);
			state = initedState;
			semaphore = SML::Semaphore_t::Free;

			// Call MSP init if needed
			if (mspInit)
			{
				mspInit();
			}
		}

		/**
		 * @brief Logger constructor for non-blocking logger process.
		 * 
		 * @param handler Pointer to external function for handling buffer transfer(printing).
		 * @param waitExtHandler Pointer to external function for handling wait states.
		 * @param fix Prefix C-string. Has to be NULL terminated.
		 * @param tickExtHandler Pointer to external function for getting tick.
		 * @param initedState Logger initial state. See \ref SML::State_t
		 * @param mspInit Pointer to external function for MSP init.
		 * @param mspDeinit Pointer to external function for MSP deinit.
		 * @return No return value.
		 */
		Logger(SML::print_handler_f handler, SML::ext_handler_f waitExtHandler, const char* fix = "", SML::ext_handler_u32_f tickExtHandler = nullptr, SML::State_t initedState = SML::State_t::On, SML::ext_handler_f mspInit = nullptr, SML::ext_handler_f mspDeinit = nullptr) : Logger(handler, fix, initedState, mspInit, mspDeinit)
		{
			// Save handlers for non-blocking process
			waitHandler = waitExtHandler;
			tickHandler = tickExtHandler;
		
			// Call MSP init if needed
			if (mspInit)
			{
				mspInit();
			}		
		}
		
		/**
		 * @brief Logger deconstructor.
		 * 
		 * @return No return value.
		 */
		~Logger(void)
		{
			// Call MSP deinit if needed
			if (mspDeinitHandler)
			{
				mspDeinitHandler();
			}	

			fill(this, 0, sizeof(Logger<N>));
		}

		// METHOD DEFINITIONS
		/**
		 * @brief Print constant C-string.
		 * 
		 * @param str Pointer to C-string.
		 * @param len Length of \c str
		 * @return \c SML::Return_t::Timeout if process timeouted.
		 * @return \c SML::Return_t::Nok if logger is turned off.
		 * @return \c SML::Return_t::Ok on success.
		 */
		SML::Return_t print(const char* str, const uint16_t len)
		{
			// Abort if logger is turned off
			if (getState() == SML::State_t::Off)
			{
				return SML::Return_t::Nok;
			}

			// Output prefix if exists
			if (prefixLen)
			{
				if (out(prefix, prefixLen) != SML::Return_t::Ok)
				{
					return SML::Return_t::Timeout;
				}
			}

			return out(str, len);
		}

		/**
		 * @brief Print constant C-string.
		 * 
		 * @param str Pointer to C-string. Has to be NULL terminated.
		 * @return \c SML::Return_t::Timeout if process timeouted.
		 * @return \c SML::Return_t::Nok if logger is turned off.
		 * @return \c SML::Return_t::Ok on success.
		 */
		inline SML::Return_t print(const char* str)
		{
			return print(str, SML::len(str));		
		}

		/**
		 * @brief Format and print string.
		 * 
		 * This method uses variable argument list and \c vsnprintf function for string formating.
		 * 
		 * @param str Pointer to C-string.
		 * @param ... Variable arguments.
		 * @return \c SML::Return_t::Timeout if process timeouted.
		 * @return \c SML::Return_t::Nok if logger is turned off.
		 * @return \c SML::Return_t::Ok on success.
		 */
		SML::Return_t printf(const char* str, ...)
		{
			// Abort if logger is turned off
			if (getState() == SML::State_t::Off)
			{
				return SML::Return_t::Nok;
			}

			// Format input C-string with variable arguments
			va_list args;
			va_start(args, str);	
			uint16_t len = vsnprintf(buffer, sizeof(buffer), str, args);
			va_end(args);

			// Output prefix
			if (prefixLen)
			{
				if (out(prefix, prefixLen) != SML::Return_t::Ok)
				{
					return SML::Return_t::Timeout;
				}
			}

			return out(buffer, len);	
		}

		/**
		 * @brief Get size of logger's buffer for \ref printf method.
		 * 
		 * @return Size of logger's buffer.
		 */
		inline uint16_t size(void) const
		{
			// Return length of logger buffer
			return sizeof(buffer);
		}

		/**
		 * @brief Get logger state.
		 * 
		 * @return \c SML::State_t::Off if logger is turned off.
		 * @return \c SML::State_t::On if logger is turned on.
		 */
		inline SML::State_t getState(void) const
		{
			return state;	
		}

		/**
		 * @brief Set logger state.
		 * 
		 * @param newState New logger status. See \ref SML::State_t
		 * @return No return value.
		 */
		inline void setState(const SML::State_t newState)
		{
			state = newState;		
		}

		/**
		 * @brief Release logger's semaphore in non-bloking process.
		 *
		 * @return No return value. 
		 */
		inline void done(void)
		{
			semaphore = SML::Semaphore_t::Free;
		}

		/**
		 * @brief Check if logger is ready for new print.
		 * 
		 * @return \c SML::Answer_t::No if logger is not ready.
		 * @return \c SML::Answer_t::Yes if logger is ready.
		 */
		SML::Answer_t isReady(void)
		{
			if (semaphore == SML::Semaphore_t::Free)
			{
				return SML::Answer_t::Yes;
			}

			return SML::Answer_t::No;
		}


		private: 
		// VARIABLES
		char buffer[N] = { '\0' }; /**< @brief Buffer for \ref printf method. */
		uint8_t prefixLen = 0; /**< @brief Length of \ref prefix */
		SML::State_t state = SML::State_t::On; /**< @brief Logger state. */
		SML::Semaphore_t semaphore = SML::Semaphore_t::Free; /**< @brief Logger process semaphore. */
		const char* prefix; /**< @brief Logger prefix (C-string). Has to be NULL terminated. */
		SML::print_handler_f printHandler = nullptr; /**< @brief Pointer to external function that handles buffer transfer. */
		SML::ext_handler_f mspDeinitHandler = nullptr; /**< @brief Pointer to function for MSP deinit. */
		SML::ext_handler_f waitHandler = nullptr; /**< @brief Pointer to external function for handling wait states. */
		SML::ext_handler_u32_f tickHandler = nullptr; /**< @brief Pointer to external function for getting tick. */

		// METHOD DEFINITIONS
		/**
		 * @brief Handle semaphore and calls \ref printHandler
		 * 
		 * @param str Pointer to C-string.
		 * @param len Length of C-string pointed by \c str
		 * @return \c SML::Return_t::Timeout process timeouted.
		 * @return \c SML::Return_t::Ok on success. 
		 */
		SML::Return_t out(const char* str, const uint16_t len)
		{
			// If print process is non-blocking
			if (waitHandler)
			{
				if (wait() != SML::Return_t::Ok)
				{
					return SML::Return_t::Timeout;
				}
				
				semaphore = SML::Semaphore_t::Taken;
			}

			// Print string
			printHandler(str, len);
			return SML::Return_t::Ok;	
		}

		/**
		 * @brief Wait for free semaphore.
		 * 
		 * @return \c SML::Return_t::Timeout wait timeouted.
		 * @return \c SML::Return_t::Ok on success. 
		 */
		SML::Return_t wait(void)
		{
			// If tick source is provided
			if (tickHandler)
			{
				// Get current tick
				uint32_t tick = tickHandler();

				// Call wait handler if logger is not ready
				while (isReady() == SML::Answer_t::No)
				{
					// Check for timeout
					if (tickHandler() - tick > SML_LOGGER_TIMEOUT)
					{
						return SML::Return_t::Timeout;
					}

					waitHandler();
				}
			}
			else // Tick source is not provided
			{
				// Call wait handler if logger is not ready
				while (isReady() == SML::Answer_t::No)
				{
					waitHandler();
				}
			}

			return SML::Return_t::Ok;
		}
	};	

	/**
	 * @brief Copier class.
	 * 
	 * Wrapper for copy blocking or non-blocking process. User can easly switch from blocking copy process(eg., with standard \c memcpy function) to non-blocking process(eg., DMA copy process).
	 * 
	 * In case of non-blocking process, user must release process semaphore with \ref Copier::done method. 
	 */
	class Copier
	{
		public:
		// CONSTRUCTOR AND DECONSTRUCTOR DEFINITIONS
		/**
		 * @brief Copier constructor for blocking copy process.
		 * 
		 * @param extHandler Pointer to external function for handling copy operations.
		 * @return No return value.
		 */
		Copier(SML::copy_handler_f extHandler)
		{
			copyHandler = extHandler;
		}

		/**
		 * @brief Copier constructor for non-blocking copy process.
		 * 
		 * @param extHandler Pointer to external function for handling copy operations.
		 * @param waitExtHandler Pointer to external function for handling wait states.
		 * @param tickExtHandler Pointer to external function for getting tick. Not required.
		 * @param mspInit Pointer to external function for MSP init. Not required.
		 * @param mspDeinit Pointer to external function for MSP deinit. Not required.
		 * @return No return value.
		 */
		Copier(SML::copy_handler_f extHandler, SML::ext_handler_f waitExtHandler, SML::ext_handler_u32_f tickExtHandler = nullptr, SML::ext_handler_f mspInit = nullptr, SML::ext_handler_f mspDeinit = nullptr) : Copier(extHandler)
		{
			waitHandler = waitExtHandler;
			tickHandler = tickExtHandler;
			mspDeinitHandler = mspDeinit;


			// Call MSP init if needed
			if (mspInit)
			{
				mspInit();
			}
		}

		/**
		 * @brief Copier object deconstructor.
		 * 
		 * @return No return value.
		 */
		~Copier(void)
		{
			// Call MSP deinit if needed
			if (mspDeinitHandler)
			{
				mspDeinitHandler();
			}

			fill(this, 0, sizeof(SML::Copier));
		}

		// METHOD DEFINITIONS
		/**
		 * @brief Copy \c len bytes from \c source to \c destionation
		 * 
		 * @param source Pointer to address to copy from.
		 * @param destination Pointer to address to copy to.
		 * @param len Number of bytes to copy from \c source to \c destionation
		 * @return \c SML::Return_t::Timeout if copy timeouted.
		 * @return \c SML::Return_t::Nok if copy failed.
		 * @return \c SML::Return_t:Ok if copy is successful.
		 */
		SML::Return_t copy(const void* source, void* destination, const uint16_t len)
		{
			// If copy process is non-blocking
			if (waitHandler)
			{
				// Wait for semaphore to be released
				if (wait() != SML::Return_t::Ok)
				{
					return SML::Return_t::Timeout;
				}

				// Take semaphore and block new copy processes
				takeSemaphore();
			}

			// Call copy handler and return its status
			return copyHandler(source, destination, len);
		}

		/**
		 * @brief Check if copier is ready.
		 * 
		 * @return \c SML::Answer_t::No if copier is not ready.
		 * @return \c SML::Answer_t::Yes if copier is ready.
		 */
		SML::Answer_t isReady(void) const
		{
			if (semaphore == SML::Semaphore_t::Free)
			{
				return SML::Answer_t::Yes;
			}

			return SML::Answer_t::No;
		}

		/**
		 * @brief Release copier semaphore.
		 * 
		 * @return No return value.
		 */
		inline void done(void)
		{
			semaphore = SML::Semaphore_t::Free;
		}


		private:
		// VARIABLES
		SML::copy_handler_f copyHandler = nullptr; /**< @brief Pointer to external function for handling copy operation. */
		SML::ext_handler_f waitHandler = nullptr; /**< @brief Pointer to external function for handling wait states. */
		SML::ext_handler_u32_f tickHandler = nullptr; /**< @brief Pointer to external function for getting tick. */
		SML::ext_handler_f mspDeinitHandler = nullptr; /**< @brief Pointer to external function for MSP deinit. */
		SML::Semaphore_t semaphore = SML::Semaphore_t::Free; /**< @brief Copy process semaphore. */

		// METHOD DEFINITIONS
		/**
		 * @brief Take semaphore for copy process.
		 * 
		 * @return No return value.
		 */
		inline void takeSemaphore(void)
		{
			semaphore = SML::Semaphore_t::Taken;
		}

		/**
		 * @brief Wait for copier to be ready for new process.
		 * 
		 * @return \c SML::Return_t::Timeout if process timeouted.
		 * @return \c SML::Return_t::Ok on success. 
		 */
		SML::Return_t wait(void) const
		{
			// If tick source is provided
			if (tickHandler)
			{
				// Get current tick
				uint32_t tick = tickHandler();

				// Call wait handler until semaphore is released
				while (isReady() == SML::Answer_t::No)
				{
					// Check for timeout
					if (tickHandler() - tick > SML_COPY_TIMEOUT)
					{
						__SML_COPY_WARNING_LOG("Copier 0x%08X timeouted\n", this);
						return SML::Return_t::Timeout;
					}

					waitHandler();
				}
			}
			else // Tick handler is not provided
			{
				// Call wait handler until semaphore is released
				while (isReady() == SML::Answer_t::No)
				{
					waitHandler();
				}
			}

			return SML::Return_t::Ok;
		}
	};
};


#endif // __cplusplus

/** @}*/

#endif // _SML_H_


// END WITH NEW LINE
