/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_METADATA_HPP
#define BB_MULTIMEDIA_METADATA_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile MetaData.hpp <bb/multimedia/MetaData>
 *
 *
 * @brief Provides string keys for a @c QVariantMap of metadata.
 *
 * @details The @c %MetaData class provides keys for a @c QVariantMap to store
 * and retrieve metadata that is used to describe multimedia content.
 * You can also add your own metadata keys and thereby store
 * custom metadata fields in the same @c QVariantMap.
 *
 * NOTE: The documentation for each key includes the QML property name of the
 * metadata property. All values are stored as strings.
 *
 * @xmlonly
 * <qml>
 *     <class register="no"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT MetaData
{
public:

    /*!
     * @brief The @c artist key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Artist;

    /*!
     * @brief The @c genre key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Genre;

    /*!
     * @brief The @c year key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Year;

    /*!
     * @brief The @c duration key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Duration;

    /*!
     * @brief The @c title key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Title;

    /*!
     * @brief The @c description key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Description;

    /*!
     * @brief The @c width key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Width;

    /*!
     * @brief The @c height key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Height;

    /*!
     * @brief The @c pixel width key.
     *
     * @since BlackBerry 10.2.0
     */
    static const char * PixelWidth;

    /*!
     * @brief The @c pixel height key.
     *
     * @since BlackBerry 10.2.0
     */
    static const char * PixelHeight;

    /*!
     * @brief The @c uri key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Uri;

    /*!
     * @brief The @c album key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Album;

    /*!
     * @brief The @c composer key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Composer;

    /*!
     * @brief The @c disc key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Disc;

    /*!
     * @brief The @c track key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Track;

    /*!
     * @brief The @c bit_rate key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * BitRate;

    /*!
     * @brief The @c sample_rate key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * SampleRate;

    /*!
     * @brief The @c artwork_uri key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * ArtworkUri;

    /*!
     * @brief The @c latitude key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Latitude;

    /*!
     * @brief The @c longitude key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Longitude;

    /*!
     * @brief The @c orientation key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Orientation;

    /*!
     * @brief The @c shutter key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Shutter;

    /*!
     * @brief The @c aperture key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Aperture;

    /*!
     * @brief The @c focal_length key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * FocalLength;

    /*!
     * @brief The @c iso key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * ISO;

    /*!
     * @brief The @c seekable key.
     *
     * @since BlackBerry 10.0.0
     */
    static const char * Seekable;

private:
    /*! @cond PRIVATE */
    MetaData();
    ~MetaData();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::MetaData)

#endif /* BB_MULTIMEDIA_METADATA_HPP */
