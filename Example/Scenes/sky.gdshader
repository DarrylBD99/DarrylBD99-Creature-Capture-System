shader_type sky;

uniform vec3 sky_col : source_color;
uniform vec3 horizon_col : source_color;

uniform vec3 sun_col : source_color;
uniform float sun_size = .2;

void sky() {
	// Sun
	float sun_dir = distance(EYEDIR.xyz, LIGHT0_DIRECTION);
	float sun_pos = 1.0 - clamp(sun_dir / sun_size, 0.0, 1.0);

	vec4 sun = vec4(sun_col, step(sun_size, sun_pos));
	// Sky Color
	float col = clamp(EYEDIR.y / 0.2, 0, 1);
	vec3 final_col = mix(horizon_col, sky_col, col);
	COLOR = mix(final_col, sun.rgb, sun.a);
}