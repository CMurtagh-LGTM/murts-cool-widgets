#ifndef WIDGETNAME_HPP
#define WIDGETNAME_HPP

#include <glibmm/extraclassinit.h>
#include <glibmm/ustring.h>

// Calls gtk_widget_class_set_css_name() in the class init function.
class WidgetName : public Glib::ExtraClassInit
{
public:
  WidgetName(const Glib::ustring& css_name);

private:
  Glib::ustring m_css_name;
};

#endif // WIDGETNAME_HPP
