#ifndef MUSIC_HPP
#define MUSIC_HPP

#include "utils/WidgetName.hpp"

#include <gtkmm/label.h>
#include <gtkmm/widget.h>

namespace mcw::widget {
    class music : public WidgetName, public Gtk::Widget {
    public:
        music();
        ~music() override;

        void set_track(const std::string& track);
        void set_album(const std::string& album);
    protected:
        Gtk::SizeRequestMode get_request_mode_vfunc() const override;
        void measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
            int& minimum_baseline, int& natural_baseline) const override;
        void size_allocate_vfunc(int width, int height, int baseline) override;

        // Signal handler:
        void on_container_destroy();
    private:
        Gtk::Label track_label;
        Gtk::Label album_label;
    };
}

#endif // MUSIC_HPP
