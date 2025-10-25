/*!
 * @copyright
 * Copyright Research In Motion Limited, 2011-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_MEMORYINFO_HPP
#define BB_CORE_MEMORYINFO_HPP

#include <bb/LowMemoryWarningLevel>

#include <bb/Global>

#include <QObject>
#include <QScopedPointer>
#include <QtDeclarative/QtDeclarative>

namespace bb
{

class MemoryInfoPrivate;

/*!
 * @headerfile MemoryInfo.hpp <bb/MemoryInfo>
 *
 * @brief The @c %MemoryInfo class provides notifications about low device memory.
 *
 * @details Instances of this class provide a signal informing the application that device
 * memory is running low. Applications can listen for this signal to free memory to avoid potential
 * performance degradations and application crashes.
 *
 * Note that, once created, instances of this class cannot have their thread affinity changed,
 * either explicitly via @c QObject::moveToThread() or implicitly by changing the thread
 * affinity of the parent of the object. Doing so results in undefined behavior.
 *
 * @xmlonly
 * <apigrouping group="Platform/Info"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT MemoryInfo : public QObject
{
    Q_OBJECT
public:
    /*!
     * @brief Creates a new @c MemoryInfo object.
     *
     * Example usage in C++
     * @snippet libbb/MemoryInfo_constructor.cpp All
     *
     * Example usage in QML
     * @snippet libbb/MemoryInfo_constructor.qml All
     *
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit MemoryInfo(QObject *parent = 0);
    /*!
     * @example libbb/MemoryInfo_constructor.cpp
     * Example use in C++
     *
     * @example libbb/MemoryInfo_constructor.qml
     * Example use in QML
     */

    /*!
     * @brief Destroys this @c MemoryInfo object.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~MemoryInfo();

    /*!
     * @brief Returns the total amount of memory on the device in bytes.
     *
     * Example usage in C++
     * @snippet libbb/MemoryInfo_totalDeviceMemory.cpp All
     *
     * Example usage in QML
     * @snippet libbb/MemoryInfo_totalDeviceMemory.qml All
     *
     * @return The total amount of memory on the device in bytes.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE qint64 totalDeviceMemory() const;
    /*!
     * @example libbb/MemoryInfo_totalDeviceMemory.cpp
     * Example use in C++
     *
     * @example libbb/MemoryInfo_totalDeviceMemory.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the current amount of free memory on the device in bytes.
     *
     * Example usage in C++
     * @snippet libbb/MemoryInfo_availableDeviceMemory.cpp All
     *
     * Example usage in QML
     * @snippet libbb/MemoryInfo_availableDeviceMemory.qml All
     *
     * @return The current amount of free memory on the device in bytes, or -1 in
     * the event of an error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE qint64 availableDeviceMemory() const;
    /*!
     * @example libbb/MemoryInfo_availableDeviceMemory.cpp
     * Example use in C++
     *
     * @example libbb/MemoryInfo_availableDeviceMemory.qml
     * Example use in QML
     */

    /*!
     * @brief Returns the amount of memory allocated for this process in bytes.
     *
     * @details This is the amount of memory that the OS has allocated to the
     * process. Due to the structure of C/C++ memory managers (memory is
     * obtained from the OS in chunks and cached by the memory manager), a
     * call to new, delete, malloc, or free, will not necessarily change the
     * value returned by this function.
     *
     * Example usage in C++
     * @snippet libbb/MemoryInfo_memoryUsedByCurrentProcess.cpp All
     *
     * Example usage in QML
     * @snippet libbb/MemoryInfo_memoryUsedByCurrentProcess.qml All
     *
     * @return The amount of memory allocated for this process in bytes, or -1 in
     * the event of an error.
     *
     * @since BlackBerry 10.0.0
     */
    Q_INVOKABLE qint64 memoryUsedByCurrentProcess() const;
    /*!
     * @example libbb/MemoryInfo_memoryUsedByCurrentProcess.cpp
     * Example use in C++
     *
     * @example libbb/MemoryInfo_memoryUsedByCurrentProcess.qml
     * Example use in QML
     */

Q_SIGNALS:
    /*!
     * @brief Emitted when the device detects that it is running low on memory.
     *
     * @details Any slot attached to this signal is notified when the device detects that memory
     * is running low. A device in this state may experience degraded performance
     * and possibly application crashes if the situation is not rectified.
     *
     * To avoid these problems, when this signal is received the application should release as much
     * memory as possible. For example, the application could free cached items that can be re-obtained
     * later, or release memory for images that can be re-read from the file system.
     *
     * The parameter @c level provides an indication of the severity of the memory situation on the device.
     * Values for this parameter are:
     * - @c bb::LowMemoryWarningLevel::LowPriority Memory is running low and the application should deallocate
     *   unnecessary objects, to ensure that the amount of available memory does not drop critically low.
     * - @c bb::LowMemoryWarningLevel::HighPriority Memory is running critically low. Applications should
     *   deallocate unnecessary object more aggressively.
     *
     * If memory continues to run low after a high priority warning, applications may be asked to exit. This
     * exit process is identical to the application being shut down by the user, including the opportunity to
     * clean up and save application state.
     *
     * Note that the device may skip some of these indications and steps depending on whether the memory
     * situation improves or worsens over time.
     *
     * If memory continues to run low after applications are asked to exit, then applications may be terminated
     * without warning and without any chance to perform any cleanup or save any state.
     *
     * Example usage in C++
     * @snippet libbb/MemoryInfo_lowMemory.cpp Connecting to the lowMemory signal
     * @link libbb/MemoryInfo_lowMemory.cpp
     * See full example
     * @endlink
     *
     * Example use in QML
     * @snippet libbb/MemoryInfo_lowMemory.qml All
     *
     * @param level The level of the low memory warning, indicating the importance and priority
     * of the warning.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void lowMemory(bb::LowMemoryWarningLevel::Type level);
    /*!
     * @example libbb/MemoryInfo_lowMemory.cpp
     * Example use in C++
     *
     * @example libbb/MemoryInfo_lowMemory.qml
     * Example use in QML
     */
protected:
//!@cond PRIVATE
    Q_SIGNAL void lowMemory(int level);
//!@endcond

private:
//!@cond PRIVATE
    QScopedPointer<MemoryInfoPrivate> d_ptr;
    Q_DECLARE_PRIVATE(MemoryInfo);
    Q_DISABLE_COPY(MemoryInfo)
//!@endcond
};

} // namespace bb

QML_DECLARE_TYPE(bb::MemoryInfo)
#endif // BB_CORE_MEMORYINFO_HPP
