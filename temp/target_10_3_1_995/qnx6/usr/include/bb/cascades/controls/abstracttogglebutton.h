/* Copyright (C) 2011-2013 Research In Motion Limited.  */

#ifndef cascades_abstracttogglebutton_h
#define cascades_abstracttogglebutton_h

#include <bb/cascades/bbcascades_global.h>
#include <bb/cascades/controls/control.h>

namespace bb {
  namespace cascades {

    class AbstractToggleButtonPrivate;
    class Container;

    /*!
    * @brief An abstract control that can switch between two possible states.
    * 
    * The @c %AbstractToggleButton class represents a toggle control that has two possible states:
    * checked and unchecked. You can use the checked state to indicate "on" or "enabled", and
    * you can use the unchecked state to indicate "off" or "disabled".
    * 
    * @see @c ToggleButton, @c ImageToggleButton, @c CheckBox
    * 
    * @xmlonly
    * <apigrouping group="User interface/Core controls"/>
    * @endxmlonly
     *
     * @since BlackBerry 10.0.0
    */
    class BBCASCADES_EXPORT AbstractToggleButton : public Control
    {
    private:
      Q_OBJECT

        /*!
        * @brief The state of this toggle control.
        * 
        * A property value of @c true indicates the checked state of the toggle control, and
        * a property value of @c false indicates the unchecked state.
        * 
        * The default value is @c false (unchecked).
         *
         * @since BlackBerry 10.0.0
        */
        Q_PROPERTY(bool checked READ isChecked WRITE setChecked RESET resetChecked NOTIFY checkedChanged FINAL)

    public:
      /*!
      * @brief Destroys this toggle control.
       *
       * @since BlackBerry 10.0.0
      */
      virtual ~AbstractToggleButton();

      /*!
      * @brief Returns the state of this toggle control.
      *
      * @return @c true if this toggle control is checked, @c false if this toggle control is
      * unchecked.
       *
       * @since BlackBerry 10.0.0
      */
      bool isChecked() const;

      /*!
      * @brief Sets the state of this toggle control.
      *
      * @param checked If @c true this toggle control is checked, if @c false this toggle control
      * is unchecked.
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void setChecked(bool checked);

      /*!
      * @brief Resets the toggle button to its default state (unchecked).
       *
       * @since BlackBerry 10.0.0
      */
      Q_SLOT void resetChecked();

Q_SIGNALS:
      /*!
      * @brief Emitted when the state of this toggle control changes.
      *
      * @param checked The new state of this toggle control. If @c true this toggle control is
      * checked, if @c false this toggle control is unchecked.
       *
       * @since BlackBerry 10.0.0
      */
      void checkedChanged(bool checked);


    protected:
      /*! @cond PRIVATE */

      /*!
      * @brief Constructs an abstract toggle button and specifies the parent container.
      *
      * The ownership of the button is transfered to the parent if a parent is specified.
      *
      * @param parent The parent container or 0. This parameter is optional. 
      * The default is 0 if you don't specify a parent.
      */
      AbstractToggleButton(AbstractToggleButtonPrivate& pPriv, Container * parent = 0);
      /*! @endcond */


    private:
      Q_DECLARE_PRIVATE(AbstractToggleButton)
        Q_DISABLE_COPY(AbstractToggleButton)
        /*! @cond PRIVATE */
        typedef AbstractToggleButton ThisClass;
      typedef Control BaseClass;
      /*! @endcond */
    public:
      /*!
      * @brief A builder template for constructing an AbstractToggleButton.
      *
      * See AbstractToggleButton::create() for getting a concrete builder for constructing
      * an %AbstractToggleButton.
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
        * @copydoc AbstractToggleButton::setChecked()
        */
        BuilderType& checked(bool checked)
        {
          this->instance().setChecked(checked);
          return this->builder();
        }

      };
    };
  }
}

QML_DECLARE_TYPE(bb::cascades::AbstractToggleButton)

#endif

