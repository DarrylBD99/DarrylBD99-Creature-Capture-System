shader_type spatial;
render_mode blend_mix, depth_draw_opaque, depth_prepass_alpha, unshaded; //Settings needed to cast a shadow

// Overall settings
uniform bool enabled = true; // enable/disable
uniform sampler2D sprite_texture : source_color, filter_nearest; // set this in editor
uniform bool billboard = true; // billboard modes
uniform bool y_billboard = false; // y-billboard modes

uniform vec4 line_color : source_color = vec4(1.0,1.0,1.0,1.0); // Glow or outline color
uniform float glowSize: hint_range(0.0, 300) = 4.0; // Size of glow
uniform int glowDensity: hint_range(0, 30) = 5; // How many stamps to repeat in one direction
uniform int glowRadialCoverage: hint_range(0, 32) = 4; // How many directions to spread out
uniform float glowAngle: hint_range(0.0, 6.28) = 1.57; // The starting angle. More important if you want to use this as a trail.
uniform float glowSharpness: hint_range(0.0, 5.0) = 1.0; // Effect how quickly stamps become transparent as they move out
uniform float alphaThreshold: hint_range(0.0, 1.0) =  0.2; // Alpha level a pixel should be considered a glow

void vertex() {
    vec2 texture_size = vec2(textureSize(sprite_texture,0));
    vec4 texture_pixel_size = vec4(10.0);

    if (y_billboard) {
        mat4 modified_model_view = VIEW_MATRIX * mat4(
            INV_VIEW_MATRIX[0] * texture_pixel_size,
            vec4(0.0, 1.0, 0.0, 0.0) * texture_pixel_size,
            INV_VIEW_MATRIX[2] * texture_pixel_size,
            MODEL_MATRIX[3]
        );

        MODELVIEW_MATRIX = modified_model_view;
    }

    if (billboard) {
        mat4 modified_model_view = VIEW_MATRIX * mat4(
            INV_VIEW_MATRIX[0] * texture_pixel_size,
            INV_VIEW_MATRIX[1] * texture_pixel_size,
            INV_VIEW_MATRIX[2] * texture_pixel_size,
            MODEL_MATRIX[3]
        );

        MODELVIEW_MATRIX = modified_model_view;
    }
}

//Goes through every single pixle and does thing
void fragment() {
	vec4 col = texture(sprite_texture, UV); // Gets color at uv position of pixel

	// Sets source image as default pixel
	ALBEDO = col.rgb;
	ALPHA = col.a;

	vec2 pixel_size = 1.0 / vec2(textureSize(sprite_texture, 0)); // Set pixel size
	float alph = 0.0; // Start with a 0 alpha to add to with each check
	for (int i = 0; i < glowRadialCoverage; i++) { // Goes around in a circle
		for (int j = 0; j < glowDensity; j++) { // Extends out
			float radians360 = 6.28;
			// The angle from which to grab pixel information
			float angle = (radians360 / float(glowRadialCoverage))*float(i+1) + glowAngle;
			// The distance to reach to grab pixel information
			float dist = glowSize * float(j + 1) / float(glowDensity);
			// Pixel coordinate to grab
			vec2 pixel_coor = vec2( sin(angle) , cos(angle) );
			// Gets the pixel based on the previous information
    		vec4 tex = texture(sprite_texture, UV + pixel_coor * pixel_size * dist);

			// Sharpness. If you don't care about this, enable the next line and delete the next 3
			//alph += tex.a * line_color.a;
			float distFrom = float(glowDensity-j) / float(glowDensity); // Distance iteration number (how far out)
			float sharpness = mix(0.0, 1.0, pow(distFrom, glowSharpness) ); // Figure out sharpness level, interplote with distance and Glow Sharpness modifier
			alph += (tex.a * line_color.a) * sharpness; // Apply sharpness
		}
	}

	// Adds outline if this part of the image is transparent
	if (ALPHA < alphaThreshold){
		ALBEDO = line_color.rgb;
		ALPHA = alph;
	}

	// Enabling this line will cut out the image and leave the outline
	//ALPHA -= col.a * 10.0;
	// if you set blend to add, and set this as a second pass, you'll get a better glow effect
}