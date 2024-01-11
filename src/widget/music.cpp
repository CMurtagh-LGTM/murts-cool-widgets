#include "widget/music.hpp"

namespace mcw::widget {

music::music() : Glib::ObjectBase("MCWMusic"), WidgetName("mcw-music") {
    track_label.insert_at_end(*this);
    album_label.insert_at_end(*this);

    signal_destroy().connect(sigc::mem_fun(*this, &music::on_container_destroy));
}

music::~music(){
    if(!gobj()){
        return; // already destroyed
    }

    on_container_destroy();
}

void music::on_container_destroy(){
    track_label.unparent();
    album_label.unparent();
}

void music::set_track(const std::string& track){
    track_label.set_text(track);
}

void music::set_album(const std::string& track){
    album_label.set_text(track);
}

Gtk::SizeRequestMode music::get_request_mode_vfunc() const {
    return Gtk::SizeRequestMode::WIDTH_FOR_HEIGHT;
}

void music::measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
    int& minimum_baseline, int& natural_baseline) const {
    minimum_baseline = -1;
    natural_baseline = -1;

    if(orientation == Gtk::Orientation::HORIZONTAL){
        int track_min, track_nat, album_min, album_nat, ignore;
        track_label.measure(Gtk::Orientation::HORIZONTAL, for_size, track_min, track_nat, ignore, ignore);
        album_label.measure(Gtk::Orientation::HORIZONTAL, for_size, album_min, album_nat, ignore, ignore);
        minimum = track_min + album_min;
        natural = track_nat + album_nat;
    } else {
        minimum = 30;
        natural = 30;
    }
}

void music::size_allocate_vfunc(int width, int height, int baseline) {
    Gtk::Allocation child_allocation;
    child_allocation.set_x(0);
    child_allocation.set_y(0);
    child_allocation.set_width(width/2);
    child_allocation.set_height(height);

    track_label.size_allocate(child_allocation, baseline);

    child_allocation.set_x(width/2);

    album_label.size_allocate(child_allocation, baseline);
}

}
