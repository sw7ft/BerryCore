/*!
 * @copyright
 * Copyright Research In Motion Limited, 2012-2013
 * Research In Motion Limited. All rights reserved.
 */

#ifndef BB_CORE_PPSOBJECT_HPP
#define BB_CORE_PPSOBJECT_HPP

#include <bb/Global>
#include <bb/PpsAttribute>
#include <bb/PpsOpenMode>

#include <QMap>
#include <QObject>
#include <QVariantMap>

namespace bb
{
class PpsObjectPrivate;

/*!
 * @headerfile PpsObject.hpp <bb/PpsObject>
 *
 * @brief Encapsulates an object in the PPS file system. See the PPS documentation for more details.
 *
 * @xmlonly
 * <apigrouping group="Platform/Utility"/>
 * <library name="bb"/>
 * @endxmlonly 
 *
 * @since BlackBerry 10.0.0
 */
class BB_CORE_EXPORT PpsObject : public QObject
{
    Q_OBJECT

public:
    /*!
     * @brief Creates a new @c PpsObject that manages the specified object in the PPS file systems.
     * 
     * Open options may be specified as a suffix to the path, following a question mark 
     * ("?"). See the PPS documentation for more details.
     *
     * Note the PPS object must be opened via a separate call to @c open() before data can
     * be read or written.
     *
     * @param path File system path of the PPS object to encapsulate.
     * @param parent If not 0, the supplied parent will be responsible for deleting this instance.
     *
     * @since BlackBerry 10.0.0
     */
    explicit PpsObject(const QString &path, QObject *parent = 0);
    
    /*!
     * @brief Destroys this @c PpsObject and closes the PPS object if open.
     *
     * @since BlackBerry 10.0.0
     */
    virtual ~PpsObject();

    /*!
     * @brief Returns the POSIX error code for the last API called on this object.
     *
     * @return @c EOK if the last API call succeeded or the POSIX error code (from @c errno.h)
     * if the last API call failed.
     *
     * @since BlackBerry 10.0.0
     */
    int error() const;

    /*!
     * @brief Returns a human-readable description of the POSIX error code for the last API called on 
     * this object.
     *
     * @return The value returned by @c strerror() (from @c string.h) for @c error().
     *
     * @since BlackBerry 10.0.0
     */
    QString errorString() const;

    /*!
     * @brief Determine if the @c readyRead() signal will fire when data is available.
     *
     * Checks if the @c readyRead() signal will fire when the PPS object has data available
     * for reading. The @c readyRead() signal is enabled by default.
     *
     * @return A flag indicating if the @c readyRead() signal is active.
     *
     * @since BlackBerry 10.0.0
     */
    bool isReadyReadEnabled() const;

    /*!
     * @brief Checks if the PPS object is in blocking or non-blocking mode.
     *
     * In blocking mode, calling @c read() and @c write() will block until data can be read or 
     * written. In non-blocking, @c read() and @c write() will fail (@c error() returns @c EAGAIN)
     * if data cannot be read or written immediately.
     *
     * PPS objects are by default opened in non-blocking mode. Appending "?wait" to the
     * file system path defaults to blocking mode.
     *
     * Note the PPS object must be open to use this method. Otherwise, this method 
     * returns false and @c error() returns @c EBADF.
     *
     * @return A flag indicating if the PPS object uses blocking or non-blocking I/O.
     *
     * @since BlackBerry 10.0.0
     */
    bool isBlocking() const;

    /*!
     * @brief Toggles blocking or non-blocking I/O for the PPS object.
     *
     * In blocking mode, calling @c read() and @c write() will block until data can be read or
     * written. In non-blocking, @c read() and @c write() will fail (@c error() returns @c EAGAIN)
     * if data cannot be read or written immediately.
     *
     * PPS objects are by default opened in non-blocking mode. Appending "?wait" to the
     * file system path defaults to blocking mode.
     *
     * @param enable A flag indicating if the PPS object should use blocking or non-blocking I/O.
     *
     * @return A flag indicating the success of the operation. On failure, call @c error() to identify the cause.
     *
     * @note The PPS object must be open to use this method. Otherwise, this method returns @c false and @c error()
     * returns @c EBADF.
     *
     * @since BlackBerry 10.0.0
     */
    bool setBlocking(bool enable);

    /*!
     * @brief Checks if the PPS object is currently open.
     *
     * @return A flag indicating if the PPS object is open or not.
     *
     * @since BlackBerry 10.0.0
     */
    bool isOpen() const;

    /*!
     * @brief Opens the PPS object in the specified mode. 
     *
     * See @c PpsOpenMode for more details.
     *
     * If you open this @c PpsObject in some form of Subscribe mode, it assumes that you intend
     * to actively read from this object every time there is a change. Therefore, @c isReadyReadEnabled()
     * returns @c true, and the @c readyRead() signal will continue to be emitted until you call the @c read()
     * method. If you do not intend to read it every time the @c readyRead() signal is emitted, then you should
     * call @c setReadyReadEnabled(false).
     *
     * @param mode A bitfield of @c PpsOpenMode flag values.
     *
     * @return A flag indicating the success of the operation. On failure, call @c error() to identify the cause.
     *
     * @note The PPS object must be closed to used this method. Otherwise, this method 
     * returns @c false and @c error() returns @c EBUSY.
     *
     * @since BlackBerry 10.0.0
     */
    bool open(PpsOpenMode::Types mode = PpsOpenMode::PublishSubscribe);

    /*!
     * @brief Closes the previously opened PPS object.
     *
     * @return A flag indicating the success of the operation. On failure, call @c error() to identify the cause.
     *
     * @note The PPS object must be open to use this method. Otherwise, this method returns @c false and @c error()
     * returns @c EBADF.
     *
     * @since BlackBerry 10.0.0
     */
    bool close();

    /*!
     * @brief Reads the current content of PPS object. 
     *
     * If no data is available to read and the PPS object is in blocking mode, then this
     * method will block until data is available for reading. If no data is available to 
     * read and the PPS object is in non-blocking mode, then this method will fail and 
     * @c error() returns @c EAGAIN. Use the @c readyRead() signal to know when data is available 
     * for reading.
     *
     * @param ok If not 0: @c *ok is set to @c true if the read succeeded; otherwise @c *ok is set to
     * @c false.  On failure, call @c error() to identify the cause.
     *
     * @return A buffer containing the data read from the PPS object.
     *
     * @since BlackBerry 10.0.0
     */
    QByteArray read(bool * ok = 0);

    /*!
     * @brief Writes all the data in the provided buffer to the PPS object. 
     *
     * @details The size of the buffer is determined by calling @c QByteArray::size().
     *
     * If no data can be written and the PPS object is in blocking mode, then this
     * method will block until the PPS object becomes writable. If no data can be 
     * written and the PPS object is in non-blocking mode, then this method will 
     * fail and @c error() returns @c EAGAIN.
     *
     * @param byteArray The buffer that contains the data to write to the PPS object.
     *
     * @return @c true if the write succeeded, @c false otherwise.  On failure, call @c error() to identify the cause.
     *
     * @since BlackBerry 10.0.0
     */
    bool write(const QByteArray &byteArray);

    /*!
     * @brief Encodes the supplied data and writes it to the opened PPS path.
     *
     * @details The @c msg and @c dat parameters are encoded as part of the raw PPS
     * data to be sent to the opened PPS path.
     *
     * The @c msg parameter will be added as the message type. <code>'ppsData["msg"] = msg'</code>
     * The @c dat parameter will be added as the data payload. <code>'ppsData["dat"] = encode( dat )</code>
     *
     * If no data can be written and the PPS object is in blocking mode, then this
     * method will block until the PPS object becomes writable. If no data can be
     * written and the PPS object is in non-blocking mode, then this method will
     * fail and @c error() returns @c EAGAIN.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_writeMessage_qstringqvariantmap.cpp Call
     *
     * @param msg The value to be encoded as the 'msg' entry.
     * @param dat The value to be encoded as the 'dat' entry.
     *
     * @return If the entire operation is successful, EOK is returned.  If there was an error encoding
     * the supplied data, -1 will be returned.  If there was an error writing the data to the PPS path
     * the value available in @c PpsObject::error() is returned and @c PpsObject::errorString() will
     * contain a textual description of the error.  See @c PpsObject::error() and @c PpsObject::errorString()
     * for more details.
     *
     * @since BlackBerry 10.2.0
     */
    int writeMessage( const QString &msg, const QVariantMap &dat );

    /*!
     * @brief Encodes the supplied data and writes it to the opened PPS path.
     *
     * @details The @c msg, @c id and @c dat parameters are encoded as part of the raw PPS
     * data to be sent to the opened PPS path.
     *
     * The @c msg parameter will be added as the message type. <code>'ppsData["msg"] = msg'</code>
     * The @c id parameter will be added as the message identifier. <code>'ppsData["id"] = id'</code>
     * The @c dat parameter will be added as the data payload. <code>'ppsData["dat"] = encode( dat )</code>
     *
     * If no data can be written and the PPS object is in blocking mode, then this
     * method will block until the PPS object becomes writable. If no data can be
     * written and the PPS object is in non-blocking mode, then this method will
     * fail and @c error() returns @c EAGAIN.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_writeMessage_qstringqstringqvariantmap.cpp Call
     *
     * @param msg The value to be encoded as the 'msg' entry.
     * @param id The value to be encoded as the 'id' entry.
     * @param dat The value to be encoded as the 'dat' entry.
     *
     * @return If the entire operation is successful, EOK is returned.  If there was an error encoding
     * the supplied data, -1 will be returned.  If there was an error writing the data to the PPS path
     * the value available in @c PpsObject::error() is returned and @c PpsObject::errorString() will
     * contain a textual description of the error.  See @c PpsObject::error() and @c PpsObject::errorString()
     * for more details.
     *
     * @since BlackBerry 10.2.0
     */
    int writeMessage( const QString &msg, const QString &id, const QVariantMap &dat );

    /*!
     * @brief Deletes the object managed by this @c PpsObject from the PPS file system.
     *
     * @return A flag indicating the success of the operation. On failure, call @c error() to identify the cause.
     *
     * @since BlackBerry 10.0.0
     */
    bool remove();

    /*!
     * @brief Read PPS data into a @c QVariantMap.
     *
     * Attributes in the PPS file are decoded as follows:
     * @li number - Decoded to a @c double.  <code>'doubleVal:n:10.5'</code> is accessed as
     *              <code>'double val = ppsData.value("doubleVal").toDouble();'</code>
     * @li boolean - Decoded to a @c bool.  <code>'boolVal:b:true'</code> is accessed as
     *               <code>'bool val = ppsData.value("boolVal").toBool();'</code>
     * @li string - Decoded as UTF8 data to a @c QString.  <code>'strVal::test'</code> is accessed as
     *              <code>'QString val = ppsData.value("strVal").toString();'</code>
     * @li json array - Decoded to a @c QVariantList.  <code>'arrayVal:json:[10,20]'</code> is accessed as
                    <code>'QVariantList val = ppsData.value("arrayVal").toList();'</code>
     * @li json object - Decoded to a @c QVariantMap.  <code>'objectVal:json:{"val1":10, "val2":20}'</code>
     *              is accessed as <code>'QVariantMap val = ppsData.value("objectVal").toMap();'</code>
     * @li json null - Decoded as an invalid @c QVariant.
     *
     * @param rawData The raw PPS data.
     * @param ok If not 0: @c *ok is set to @c true if the data could be decoded; otherwise @c *ok is set
     * to @c false.
     *
     * @return A @c QVariantMap containing the data in a hierarchical format.
     *
     * @since BlackBerry 10.0.0
     */
    static QVariantMap decode( const QByteArray &rawData, bool * ok = 0 );

    /*!
     * @brief Read PPS data into a @c PpsAttribute map.
     *
     * @see @c PpsAttribute
     *
     * @param rawData The raw PPS data.
     * @param ok If not 0: @c *ok is set to @c true if the data could be decoded; otherwise @c *ok is set
     * to @c false.
     *
     * @return A @c QMap<QString,PpsAttribute> containing the data in a hierarchical format.
     *
     * @since BlackBerry 10.0.0
     */
    static QMap<QString, PpsAttribute> decodeWithFlags( const QByteArray &rawData, bool * ok = 0 );

    /*!
     * @brief Read PPS data into a @c PpsAttribute map.
     *
     * @see @c PpsAttribute
     * @see @c PpsObject::decodeWithFlags(const QByteArray &, bool *)
     *
     * @param rawData The raw PPS data.
     * @param objectAttribute If not 0: On success, @c *objectAttribute is set to an instance of @c PpsAttribute that
     * describes the PPS object as a whole. The object will have type @c String, which will be the name of the PPS object
     * preceded by @c '@'.  The flags will be set to reflect the object state.
     * @param ok If not 0: @c *ok is set to @c true if the data could be decoded; otherwise @c *ok is set
     * to @c false.
     *
     * @return A @c QMap<QString,PpsAttribute> containing the data in a hierarchical format.
     *
     * @since BlackBerry 10.0.0
     */
    static QMap<QString, PpsAttribute> decodeWithFlags( const QByteArray &rawData, PpsAttribute *objectAttribute, bool * ok = 0 );

    /*!
     * @brief Creates PPS data from the supplied @c QVariantMap.
     *
     * Each @c QVariant value in the map is encoded based on the runtime type:
     * @li @c double - Encoded as a number.  <code>'ppsData["doubleVal"] = 10.5;'</code> encodes as <code>'doubleVal:n:10.5'</code>
     * @li @c int - Encoded as a number.  <code>'ppsData["intVal"] = 10;'</code> encodes as <code>'intVal:n:10'</code>
     * @li <code>unsigned int</code> - Encoded as a number.  <code>'ppsData["uintVal"] = 10u;'</code> encodes as <code>'intVal:n:10'</code>
     * @li @c bool - Encoded as a boolean.  <code>'ppsData["boolVal"] = true;'</code> encodes as <code>'boolVal:b:true'</code>
     * @li @c QString - Encoded with as a UTF8 string, with default type.  <code>'ppsData["strVal"] = QString("test");'</code>
     *                  encodes as <code>'strVal::test'</code>
     * @li @c QVariantList - Encoded as a json array.  <code>'ppsData["arrayVal"] = ( QVariantList() << 10 << 20 );'</code>
     *                       encodes as <code>'arrayVal:json:[10,20]'</code>
     * @li @c QVariantMap - Encoded as a json object.  <code>'QVariantMap map; map["val1"] = 10; map["val2"] = 20; ppsData["objectVal"] = map;'</code>
                            encodes as <code>'objectVal:json:{"val1":10, "val2":20}'</code>
     * @li Invalid @c QVariant - Encoded as a json null.  <code>'ppsData["nullVal"] = QVariant();'</code> encodes as
     *                           <code>'nullVal:json:null'</code>
     *
     * @param ppsData A @c QVariantMap containing the data in a hierarchical format.
     * @param ok If not 0: @c *ok is set to @c true if the data could be encoded; otherwise @c *ok is set to @c false.
     *
     * @return A data buffer containing raw PPS data.
     *
     * @since BlackBerry 10.0.0
     */
    static QByteArray encode( const QVariantMap &ppsData, bool * ok = 0 );

    /*!
     * @brief Creates PPS data from the supplied message and data content.
     *
     * @details This method can simplify creating the PPS data to send to a PPS path.
     *
     * The @c msg parameter will be added as the message type. <code>'ppsData["msg"] = msg'</code>
     * The @c dat parameter will be added as the data payload. <code>'ppsData["dat"] = encode( dat )</code>
     *
     * For details on how the @c dat parameter is encoded, see @c PpsObject::encode.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_encodeMessage_qstringqstringqvariantmap.cpp Call
     *
     * @param msg The value to be encoded as the 'msg' entry.
     * @param dat The value to be encoded as the 'dat' entry.
     * @param ok If not 0, @c *ok is set to @c true if the data could be encoded; otherwise @c *ok is set to @c false.
     *
     * @return A data buffer containing raw PPS data.
     *
     * @since BlackBerry 10.2.0
     */
    static QByteArray encodeMessage( const QString &msg, const QVariantMap &dat, bool * ok = 0 );

    /*!
     * @brief Creates PPS data from the supplied message and data content.
     *
     * @details This method can simplify creating the PPS data to send to a PPS path.
     *
     * The @c msg parameter will be added as the message type. <code>'ppsData["msg"] = msg'</code>
     * The @c id parameter will be added as the message identifier. <code>'ppsData["id"] = id'</code>
     * The @c dat parameter will be added as the data payload. <code>'ppsData["dat"] = encode( dat )</code>
     *
     * For details on how the @c dat parameter is encoded, see @c PpsObject::encode.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_encodeMessage_qstringqstringqvariantmap.cpp Call
     *
     * @param msg The value to be encoded as the 'msg' entry.
     * @param id The value to be encoded as the 'id' entry.
     * @param dat The value to be encoded as the 'dat' entry.
     * @param ok If not 0, @c *ok is set to @c true if the data could be encoded; otherwise @c *ok is set to @c false.
     *
     * @return A data buffer containing raw PPS data.
     *
     * @since BlackBerry 10.2.0
     */
    static QByteArray encodeMessage( const QString &msg, const QString &id, const QVariantMap &dat, bool * ok = 0 );

    /*!
     * @brief Writes the supplied string to the specified PPS path.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_sendMessage_qstringqstring.cpp Call
     *
     * @param path The PPS path to which the data will be written.
     * @param message The string to be written to the PPS path.
     *
     * @return @c EOK if the call succeeded or the POSIX error code (from @c errno.h).
     *
     * @since BlackBerry 10.2.0
     */
    static int sendMessage( const QString &path, const QString &message );

    /*!
     * @brief Encodes the supplied data and writes it to the supplied PPS path.
     *
     * @details The supplied @c message will be encoded using @c PpsObject::encode() and
     * the resulting PPS data will be written to the supplied path.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_sendMessage_qstringqvariantmap.cpp Call
     *
     * @param path The PPS path to which the data will be written.
     * @param message The value to be encoded and written to the PPS path.
     *
     * @return If the entire operation is successful, @c EOK is returned.  If there was an error encoding
     * the supplied data, -1 will be returned. If the write failed the return value will be one
     * of the POSIX error codes (from @c errno.h).
     *
     * @since BlackBerry 10.2.0
     */
    static int sendMessage( const QString &path, const QVariantMap &message );

    /*!
     * @brief Encodes the supplied data and writes it to the supplied PPS path.
     *
     * @details The @c msg and @c dat parameters are encoded as part of the raw PPS
     * data to be sent to the supplied PPS path.
     *
     * The @c msg parameter will be added as the message type. <code>'ppsData["msg"] = msg'</code>
     * The @c dat parameter will be added as the data payload. <code>'ppsData["dat"] = encode( dat )</code>
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_sendMessage_qstringqstringqvariantmap.cpp Call
     *
     * @param path The PPS path to which the data will be written.
     * @param msg The value to be encoded as the 'msg' entry.
     * @param dat The value to be encoded as the 'dat' entry.
     *
     * @return If the entire operation is successful, @c EOK is returned.  If there was an error encoding
     * the supplied data, -1 will be returned. If the write failed the return value will be one
     * of the POSIX error codes (from @c errno.h).
     *
     * @since BlackBerry 10.2.0
     */
    static int sendMessage( const QString &path, const QString &msg, const QVariantMap &dat );

    /*!
     * @brief Writes the supplied data to the specified PPS path.
     *
     * Example usage in C++
     * @snippet libbb/PpsObject_sendMessage_qstringqbytearray.cpp Call
     *
     * @param path The PPS path to which the data will be written.
     * @param ppsData The data to be written to the PPS path.
     *
     * @return @c EOK if the call succeeded or the POSIX error code (from @c errno.h).
     *
     * @since BlackBerry 10.2.0
     */
    static int sendMessage( const QString &path, const QByteArray &ppsData );

public Q_SLOTS:
    /*!
     * @brief Toggles whether the @c readyRead() signal will fire when the PPS object has 
     * data available for reading. 
     *
     * The @c readyRead() signal is enabled by default.
     *
     * @param enable A flag indicating if the @c readyRead() signal is active.
     *
     * @ingroup Slots
     *
     * @since BlackBerry 10.0.0
     */
    void setReadyReadEnabled(bool enable);

Q_SIGNALS:
    /*!
     * @brief Indicates the PPS object has data available for reading.
     *
     * @ingroup Signals
     *
     * @since BlackBerry 10.0.0
     */
    void readyRead();

private:
//!@cond PRIVATE
    QScopedPointer<PpsObjectPrivate> d_ptr;
    Q_DECLARE_PRIVATE(PpsObject)
    Q_DISABLE_COPY(PpsObject)
//!@endcond
};

} // namespace bb

#endif // BB_CORE_PPSOBJECT_HPP
