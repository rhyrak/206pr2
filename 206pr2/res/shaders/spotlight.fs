#version 330

// Output fragment color
out vec4 finalColor;

#define     MAX_SPOTS			2
#define		RADIUS				120
#define		INNER				30

// Inputs
// array of spotlight positions
uniform vec2 spots[MAX_SPOTS];


void main()
{

	float alpha;
	vec2 pos = vec2(gl_FragCoord.x, gl_FragCoord.y);

	float d = 8000; // some high value
	float di = 0;

    for (int i = 0; i < MAX_SPOTS; i++)
    {
		di = distance(pos, spots[i]);
		if (d > di) d = di;
    }
    
    // d now equals distance to nearest spot...
    if (d > RADIUS) {
		alpha = 1.0;
	} else {
		if (d < INNER) {
			alpha = 0.0;
		} else {
			alpha = (d - INNER) / (RADIUS - INNER);
		}
	}

    finalColor = vec4( 0, 0, 0, alpha);
}
