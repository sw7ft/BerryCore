/*!
 * Copyright (C) 2009-2014 BlackBerry Limited. All rights reserved.
 */

#ifndef BB_MULTIMEDIA_OVERLAYSTYLE_HPP
#define BB_MULTIMEDIA_OVERLAYSTYLE_HPP

#include <bb/multimedia/Global>

#include <QtDeclarative/QtDeclarative>
#include <QObject>

namespace bb
{
namespace multimedia
{

/*!
 * @headerfile OverlayStyle.hpp <bb/multimedia/OverlayStyle>
 *
 *
 * @brief Represents the various overlay styles used by a
 * @c NowPlayingConnection.
 *
 * @xmlonly
 * <qml>
 *     <class register="yes"/>
 * </qml>
 * <apigrouping group="Multimedia/MediaPlayer"/>
 * <library name="bbmultimedia"/>
 * @endxmlonly
 *
 * @since BlackBerry 10.0.0
 */
class BB_MULTIMEDIA_EXPORT OverlayStyle
{
    Q_GADGET
    Q_ENUMS(Type)

public:

    /*!
     * @enum Type
     *
     * @brief Represents various @c NowPlayingConnection overlay styles.
     *
     * @since BlackBerry 10.0.0
     */
    enum Type {

        /*!
         * @brief Indicates that a plain overlay style is to be used, which will not show metadata.
         *
         * @since BlackBerry 10.0.0
         */
        Plain = 0,

        /*!
         * @brief Indicates that a fancy overlay style should be used to display now playing metadata.
         *
         * @since BlackBerry 10.0.0
         */
        Fancy = 1,
    };

private:
    /*! @cond PRIVATE */
    OverlayStyle();
    ~OverlayStyle();
    /*! @endcond */
};

} /* namespace multimedia */
} /* namespace bb */

QML_DECLARE_TYPE(bb::multimedia::OverlayStyle)

#endif /* BB_MULTIMEDIA_OVERLAYSTYLE_HPP */
