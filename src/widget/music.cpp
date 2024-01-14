#include "widget/music.hpp"

namespace mcw::widget {

music::music() : Glib::ObjectBase("MCWMusic"), WidgetName("mcw-music") {
    art_image.set_content_fit(Gtk::ContentFit::COVER);
    art_image.insert_at_end(*this);
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

void music::set_art(Glib::RefPtr<Gdk::Texture> art){
    art_image.set_paintable(art);
}

Gtk::SizeRequestMode music::get_request_mode_vfunc() const {
    return Gtk::SizeRequestMode::WIDTH_FOR_HEIGHT;
}

void music::measure_vfunc(Gtk::Orientation orientation, int /*for_size*/, int& minimum, int& natural,
    int& minimum_baseline, int& natural_baseline) const {
    minimum_baseline = -1;
    natural_baseline = -1;

    if(orientation == Gtk::Orientation::HORIZONTAL){
        int track_min, track_nat, album_min, album_nat, ignore;
        track_label.measure(Gtk::Orientation::HORIZONTAL, 30, track_min, track_nat, ignore, ignore);
        album_label.measure(Gtk::Orientation::HORIZONTAL, 30, album_min, album_nat, ignore, ignore);
        minimum = track_min + album_min;
        natural = track_nat + album_nat;
    } else {
        minimum = 30;
        natural = 30;
    }
}

void music::size_allocate_vfunc(int width, int height, int baseline) {
    Gtk::Allocation full_allocation;
    full_allocation.set_x(0);
    full_allocation.set_y(0);
    full_allocation.set_width(width);
    full_allocation.set_height(height);
    art_image.size_allocate(full_allocation, 0);

    int track_nat, album_nat, ignore;
    track_label.measure(Gtk::Orientation::HORIZONTAL, 30, ignore, track_nat, ignore, ignore);
    album_label.measure(Gtk::Orientation::HORIZONTAL, 30, ignore, album_nat, ignore, ignore);

    Gtk::Allocation child_allocation;
    child_allocation.set_x(0);
    child_allocation.set_y(0);
    child_allocation.set_width(track_nat);
    child_allocation.set_height(height);
    track_label.size_allocate(child_allocation, baseline);

    child_allocation.set_x(track_nat);
    child_allocation.set_width(album_nat);
    album_label.size_allocate(child_allocation, baseline);

}

}
