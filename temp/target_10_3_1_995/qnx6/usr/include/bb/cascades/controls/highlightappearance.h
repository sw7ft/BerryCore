/* Copyright (C) 2013 Research In Motion Limited.  */

#ifndef CASCADES_HIGHLIGHTAPPEARANCE_H
#define CASCADES_HIGHLIGHTAPPEARANCE_H

#include <bb/cascades/bbcascades_global.h>
#include <QObject>
#include <QtDeclarative/QtDeclarative>

namespace bb {
namespace cascades {
    /*!
     * @brief Represents a highlight appearance for a @c CustomListItem.
     *
     * You can use the @c %HighlightAppearance class to indicate the type of highlighting that
     * you want to use for a @c %CustomListItem when it's selected. For example, the item could
     * use full highlighting (the entire item is highlighted), frame highlighting (only a small
     * frame on top of the item is highlighted), or no highlighting.
     *
     * @xmlonly
     * <apigrouping group="User interface/List"/>
     * @endxmlonly
     *
     * @since BlackBerry 10.2.0
     */
    class BBCASCADES_EXPORT HighlightAppearance {
    private:
        Q_GADGET
        Q_ENUMS(Type)

    public:
        /*!
         * @brief An enumeration of possible highlight appearances for a @c CustomListItem.
         *
         * @since BlackBerry 10.2.0
         */
        enum Type {
            /*!
             * @brief Represents the default highlight appearance.
             *
             * Currently, the default highlight appearance is @c HighlightAppearance::Full.
             *
             * @since BlackBerry 10.2.0
             */
            Default = 0,

            /*!
             * @brief Represents the full highlight appearance.
             *
             * When this highlight appearance is used, the whole item will be highlighted. Note
             * that if the whole item is covered and no transparancy is set on the content, the
             * highlight isn't visible.
             *
             * @since BlackBerry 10.2.0
             */
            Full = 1,

            /*!
             * @brief Represents the frame highlight appearance.
             *
             * When this highlight appearance is used, a small frame will be on top of the item as
             * the highlight.
             *
             * @since BlackBerry 10.2.0
             */
            Frame = 2,

            /*!
             * @brief Represents no highlight appearance.
             *
             * When this highlight appearance is used, no highlight is shown. This can be useful when
             * you want to implement and use your own highlight.
             *
             * @since BlackBerry 10.2.0
             */
            None = 3
        };

    private:
        /* @cond PRIVATE */
        HighlightAppearance();
        ~HighlightAppearance();
        /* @endcond */
    };


}
}

#endif // CASCADES_HIGHLIGHTAPPEARANCE_H
