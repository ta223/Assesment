#include "Header.h"
#include <stdio.h>

my_geometry_object::my_geometry_object() {

}

my_geometry_build::my_geometry_build(class my_geometry_object &object_first_node, class my_geometry_object &ref_object_first_node,
	const char* _rdb_name_)
	:object_list(&object_first_node), reference_object_list(&ref_object_first_node), rdb_name(_rdb_name_) {

}

class my_geometry_build *my_geometry_build::get_base_pointer() {
	return this;
}


void my_geometry_build::print_content() {
	printf("          Contains: %s:%d-%s (%ld)\n", rdb_name,
		object_list.first_node->toc->id, object_list.first_node->toc->data.object->name,attrib_id);
}


my_geometry_feature::my_geometry_feature(class my_geometry_object &object_first_node,
	class my_geometry_object &ref_object_first_node, const char* _rdb_name_, const char *_orig_rdb_name_, const char *_name_) :
	my_geometry_build(object_first_node, ref_object_first_node, _rdb_name_), build(my_geometry_build::get_base_pointer()),
	orig_rdb_name(_orig_rdb_name_), name(_name_){

}

void my_geometry_feature::print_content() {

	class my_geometry_build *ptr;
	int i = 0;
	for (ptr = build.first_node; i < build.n_nodes; ptr = ptr->next)
		ptr->print_content();

}


my_feature_s::my_feature_s(class my_geometry_object &object_first_node,
	class my_geometry_object &ref_object_first_node, const char* _rdb_name_, const char *_orig_rdb_name_, const char *_name_):
	my_geometry_feature(object_first_node, ref_object_first_node, _rdb_name_, _orig_rdb_name_, _name_){

}

void my_feature_window_feature::print(const char *str) {
	printf("%s\n", str);
}

void my_feature_category_feature::print(const char *str) {
	printf("  %s\n", str);
}

void my_feature_geometry_feature::print(const char *str) {

	printf("    %s\n", str);
	my_feature_s::my_geometry_feature::print_content();

}

void my_light_feature::print(const char *str) {
	printf("    %s\n", str);
}

void my_annotation_feature::print(const char *str) {
	printf("    %s\n", str);
}

void my_overlay_feature::print(const char *str) {
	printf("    %s\n", str);
}

void my_mgrid_feature::print(const char *str) {
	printf("    %s\n", str);
}

my_display_attributes::my_display_attributes() {

}

class my_display_attributes *my_display_attributes::get_base_pointer() {
	return this;
}

void my_display_attributes::print() {
	printf("Attrib ID %ld\n", sub_id);
}

template<class my_feature_type>
my_display_list_s::my_display_list_s(): 
	my_feature_type(), my_display_attributes(), attributes(my_display_attributes::get_base_pointer()) {

}


template<class my_feature_type>
void my_display_list_s::print_display_list() {

	my_feature_type::print((char *)my_expand_entry());	

	class my_display_attributes* ptr = NULL;
	int i = 0;

	for (ptr = attributes.first_node; i < attributes.n_nodes; i++, ptr = ptr->next) {
		ptr->print();
	}

	

}