/* Copyright (C) 2012-2013 Research In Motion Limited.  */

#ifndef cascades_abstractcontentsecurity_h
#define cascades_abstractcontentsecurity_h

#include <bb/system/SecurityPerimeter.hpp>
#include <bb/cascades/BaseObject>

namespace bb {
    namespace cascades {

      class AbstractContentSecurityPrivate;

         /*!
         *
         * @brief The base class for all content security subclasses.
         *
         * @see ContentSecurity 
         * 
         * @c %ContentSecurity also describes more how ContentSecurity
         * can be used.
         * @xmlonly
         * <apigrouping group="User interface/Resources"/>
         * @endxmlonly
          *
          * @since BlackBerry 10.0.0
         */
      class BBCASCADES_EXPORT AbstractContentSecurity : public BaseObject {
          Q_OBJECT

      public:
        virtual ~AbstractContentSecurity();

        /*!
        * @brief The default security perimeter
        *
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bb::system::SecurityPerimeter::Type defaultPerimeter
            READ defaultPerimeter
            WRITE setDefaultPerimeter
            RESET resetDefaultPerimeter
            NOTIFY defaultPerimeterChanged
            FINAL);

        /*!
        * @brief Gets the default security perimeter
        *
        * @return The security perimeter. The default value is Default.
         *
         * @since BlackBerry 10.0.0
        */
        bb::system::SecurityPerimeter::Type defaultPerimeter();

        /*!
        * @brief Sets the default security perimeter
        *
        * @param defaultPerimeter
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void setDefaultPerimeter(bb::system::SecurityPerimeter::Type defaultPerimeter);

        /*!
        * @brief Resets the default perimeter
        *
        * Resets the default perimeter to Default
         *
         * @since BlackBerry 10.0.0
        */
        Q_SLOT void resetDefaultPerimeter();

Q_SIGNALS:
        /*!
        * @brief Emitted when the default perimeter has changed.
        *
        * @param newDefaultPerimeter The new default perimeter
        *
        * @since BlackBerry 10.0.0
        */
        void defaultPerimeterChanged(const bb::system::SecurityPerimeter::Type newDefaultPerimeter);

        /*! @cond PRIVATE */
      protected:
        AbstractContentSecurity(AbstractContentSecurityPrivate &_d_ptr, BaseObject *parent = 0);
        /*! @endcond */

      private:
        /*! @cond PRIVATE */
        Q_DECLARE_PRIVATE(AbstractContentSecurity)
        Q_DISABLE_COPY(AbstractContentSecurity)
        /*! @endcond */

      public:
        /*! @cond PRIVATE */
        typedef AbstractContentSecurity ThisClass;
        typedef BaseObject BaseClass;
        /*! @endcond */

        /*!
        * @brief A builder template for constructing an AbstractContentSecurity
        *
        * @since BlackBerry 10.0.0
        */
        template <typename BuilderType, typename BuiltType>
        class TBuilder : public BaseClass::TBuilder<BuilderType, BuiltType>
        {
        protected:
            TBuilder(BuiltType* node) : BaseClass::TBuilder<BuilderType, BuiltType>(node)
            {
            }

        public:
            /*!
            * @copydoc AbstractContentSecurity::setDefaultPerimeter()
            */
            BuilderType& defaultPerimeter(bb::system::SecurityPerimeter::Type defaultPerimeter)
            {
                this->instance().setDefaultPerimeter(defaultPerimeter);
                return this->builder();
            }
        };
      };
    }
}

#endif /* cascades_abstractcontentsecurity_h */
