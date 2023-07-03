#if !defined __MODELGEOMETRY_INCLUDED__
#define __MODELGEOMETRY_INCLUDED__
#define MODELGEOMETRY_MODELS		(20000)

enum e_modelsize_aabb3_info {
	Float:E_MIN_X,
	Float:E_MIN_Y,
	Float:E_MIN_Z,
	Float:E_MAX_X,
	Float:E_MAX_Y,
	Float:E_MAX_Z,
};

enum e_modelsize_aabb3_line {
	E_MODELID,
	Float:E_MIN_X,
	Float:E_MIN_Y,
	Float:E_MIN_Z,
	Float:E_MAX_X,
	Float:E_MAX_Y,
	Float:E_MAX_Z,
};
static stock Model_AABB3[MODELGEOMETRY_MODELS][e_modelsize_aabb3_info];

stock ModelSize_init(const filepath[]) {
	new File:f = fopen(filepath, io_read),
		line_info[e_modelsize_aabb3_line],
		modelid
	;
	if( f ) {
		while( fblockread(f, line_info, sizeof(line_info)) == sizeof(line_info) ) {
			modelid = line_info[E_MODELID];
			if( modelid > 0 && modelid < MODELGEOMETRY_MODELS ) {
				memcpy(Model_AABB3[modelid], line_info[e_modelsize_aabb3_line:1], 0, 4 * sizeof(line_info), sizeof(line_info));
			}
		}
		fclose(f);
	} else {
		printf("ModelSize_init: cant load from (%s).", filepath);
	}
}

stock ModelGeom_parseBoxBounds(
	const aabb_info[e_modelsize_aabb3_info],
	&Float:min_x,
	&Float:min_y,
	&Float:min_z,
	&Float:max_x,
	&Float:max_y,
	&Float:max_z
) {
	min_x = aabb_info[E_MIN_X];
	min_y = aabb_info[E_MIN_Y];
	min_z = aabb_info[E_MIN_Z];
	max_x = aabb_info[E_MAX_X];
	max_y = aabb_info[E_MAX_Y];
	max_z = aabb_info[E_MAX_Z];
}

stock ModelGeom_getVisualBoxBounds(
	const modelid,
	&Float:min_x,
	&Float:min_y,
	&Float:min_z,
	&Float:max_x,
	&Float:max_y,
	&Float:max_z
) {
	if( modelid > 0 && modelid < MODELGEOMETRY_MODELS ) {
		ModelGeom_parseBoxBounds(Model_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	} else {
		min_x = min_y = min_z = max_x = max_y = max_z = 0.0;
	}
}

stock ModelGeom_getVisualBoxSize(
	const modelid,
	&Float:size_x,
	&Float:size_y,
	&Float:size_z
) {
	new Float:min_x, Float:min_y, Float:min_z,
		Float:max_x, Float:max_y, Float:max_z
	;
	ModelGeom_parseBoxBounds(Model_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	size_x = max_x - min_x;
	size_y = max_y - min_y;
	size_z = max_z - min_z;
}

stock ModelGeom_getVisualCenter(
	const modelid,
	&Float:pos_x,
	&Float:pos_y,
	&Float:pos_z
) {
	new Float:min_x, Float:min_y, Float:min_z,
		Float:max_x, Float:max_y, Float:max_z
	;
	ModelGeom_parseBoxBounds(Model_AABB3[modelid], min_x, min_y, min_z, max_x, max_y, max_z);
	size_x = 0.5 * (max_x - min_x);
	size_y = 0.5 * (max_y - min_y);
	size_z = 0.5 * (max_z - min_z);
}
#endif
