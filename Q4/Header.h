#pragma once
#include "String.h"
#include "LinkedList.h"

typedef enum {
	MY_WINDOW_FEATURE,
	MY_CATEGORY_FEATURE,
	MY_GEOMETRY_FEATURE,
	MY_LIGHT_FEATURE,
	MY_ANNOTATION_FEATURE,
	MY_OVERLAY_FEATURE,
	MY_MGRID_FEATURE
} my_feature_type_e;

typedef enum {
	MY_LIGHT_FEATURE_TYPE_NORMAL,
	MY_LIGHT_FEATURE_TYPE_DISTANT,
	MY_LIGHT_FEATURE_TYPE_SPOTLIGHT,
	MY_LIGHT_FEATURE_TYPE_AMBIENT
} my_light_feature_type_e;

/*this class is not a base for any other class - to be used in LinkedList form in the class my_geometry_build*/
class my_geometry_object : public Linker<my_geometry_object>{

public:
	my_geometry_object();

private:
	rdb_toc toc;
	my_geometry_preload *preload, *lod;
	bool deactivated, uses_pseudo_time, free_preload;
	friend class my_geometry_build;

};


/*Base class for my_geometry_feature*/
class my_geometry_build : public Linker<my_geometry_build>{	

public:
	my_geometry_build(class my_geometry_object &object_first_node, 
		class my_geometry_object &ref_object_first_node, const char* _rdb_name_);	
	class my_geometry_build *get_base_pointer();
	virtual void print_content();

protected:
	class LinkedList <class my_geometry_object> object_list;
	class LinkedList <class my_geometry_object> reference_object_list;
	const String rdb_name;	
	long int attrib_id;

private:
	my_manipulation* manipulation_list;
	int ref_timestep;
	bool selected;
	

};

class my_geometry_feature : public my_geometry_build{

public:
	my_geometry_feature(class my_geometry_object &object_first_node,
		class my_geometry_object &ref_object_first_node, const char* _rdb_name_,
		const char *_orig_rdb_name_, const char *_name_);	

	void print_content();
	class LinkedList <class my_geometry_build> build;

private:
	const String orig_rdb_name, name;
	bool mixed_build_timeline;
	
};

//-----------------------------------------------------------------------------------------------------------------------------------------

template<typename data_type>
struct Point_3D{data_type x, y, z;};

class my_light_feature {
	
public:
	
	my_light_feature_type_e type;	//enum
	const String id;
	
	bool camera_relative;
	struct Point_3D<float> local_light_position, target_position;
	float cone;
	float edge; 
	float concentration; 
	float r, g, b;
};

class my_feature_s :public Linker<class my_feature_s>, public my_geometry_feature{

public:
	my_feature_s(class my_geometry_object &object_first_node,
		class my_geometry_object &ref_object_first_node, const char* _rdb_name_, const char *_orig_rdb_name_, const char *_name_);
	virtual void print(const char *str) = 0;
	//my_feature_type_e type;
	union {
		my_category_feature *category;
		my_window_feature *window;
		class my_light_feature *light;
		class my_annotation_feature *annotation;
		class my_overlay_feature *overlay;
		class my_mgrid_feature *mgrid;
	} feature;

};

class my_feature_window_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_feature_category_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_feature_geometry_feature : public my_feature_s{
public:
	void print(const char *str);
};

class my_light_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_annotation_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_overlay_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_mgrid_feature : public my_feature_s {
public:
	void print(const char *str);
};

class my_display_attributes {
public:
	my_display_attributes();
	class my_display_attributes *get_base_pointer();
	void print();
	/*whatever data it has*/
	long int sub_id;
};

template <class my_feature_type>	//one of the derived classes of my_feature_s
class my_display_list_s : public Linker<class my_display_list_s>, public my_feature_type, public my_display_attributes {

public:
	my_display_list_s();
	
	const String my_expand_entry();
	void print_display_list();

	/*data*/
	class LinkedList<class my_display_attributes> attributes;
	bool expanded;
	bool selected;
	HC_KEY segment_key;
	my_display_state_e state;
	int parse_op_no;

	my_key_list *display_keys;

	my_geometry_marker_info *marker;

};