#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <gtkmm/label.h>
#include <gtkmm/picture.h>
#include <gtkmm/widget.h>

#include "utils/WidgetName.hpp"

namespace mcw::widget {
    class music
        : public utils::WidgetName
        , public Gtk::Widget {
    public:
        music();
        ~music() override;

        void set_track(const std::string& track);
        void set_album(const std::string& album);
        void set_art(Glib::RefPtr<Gdk::Texture> art);

    protected:
        Gtk::SizeRequestMode get_request_mode_vfunc() const override;
        void measure_vfunc(Gtk::Orientation orientation,
                           int for_size,
                           int& minimum,
                           int& natural,
                           int& minimum_baseline,
                           int& natural_baseline) const override;
        void size_allocate_vfunc(int width, int height, int baseline) override;

        // Signal handler:
        void on_container_destroy();

    private:
        Gtk::Label track_label;
        Gtk::Label album_label;
        Gtk::Picture art_image;
    };
}  // namespace mcw::widget

#endif  // MUSIC_HPP
