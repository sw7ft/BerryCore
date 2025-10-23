/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_paint_h
#define cascades_paint_h

#include <bb/cascades/bbcascades_global.h>

namespace bb {
    namespace cascades {

    class PaintDataPrivate;

    /*!
     * 
     *
     * @brief An abstract class representing a type of fill.
     *
     * Subclasses can define different ways of filling or stroking such as color, gradient or a tiled pattern.
     *
     * @xmlonly
     * <apigrouping group="User interface/Resources"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.0.0
     */
    class BBCASCADES_EXPORT Paint {
    public:
        /*!
         * @brief Destructor for @c %Paint objects.
         *
         * @since BlackBerry 10.0.0
         */
        virtual ~Paint() = 0;

        /*!
         * @brief A @c == operator for @c %Paint objects.
         *
         * Equality criteria are defined by each subclass.
         *
         * @return @c true if the objects are equal, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator==(const Paint &other) const;

        /*!
         * @brief An @c != operator for @c %Paint objects.
         *
         * @return @c true if the objects are not equal, @c false otherwise.
         *
         * @see Paint::operator==()
         *
         * @since BlackBerry 10.0.0
         */
        virtual bool operator!=(const Paint &other) const;

        /*!
         * @brief Copy constructor for @c %Paint objects.
         *
         * @since BlackBerry 10.0.0
         */
        Paint(const Paint &orig);

        /*!
         * @brief A @c = operator  for @c %Paint objects.
         *
         * @since BlackBerry 10.0.0
         */
        Paint& operator=(const Paint& other);

        /*!
         * @brief Checks whether this @c %Paint object is a @c null paint
         *
         * @return @c true if this @c %Paint object is a @c null paint, @c false otherwise.
         *
         * @since BlackBerry 10.0.0
         */
        bool isNull() const;

    protected:
        /*! @cond PRIVATE */
        Paint(PaintDataPrivate *data);
        Q_DECL_HIDDEN Paint(QSharedDataPointer<PaintDataPrivate> _d);
        QSharedDataPointer<PaintDataPrivate> d;
        friend class PaintDataPrivate;
        /*! @endcond */
    };
    
}
}

#endif	/* cascades_paint_h */
