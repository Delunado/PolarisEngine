#version 410

in vec3 position;
in vec3 normal;
in vec2 textCoord;

uniform vec3 Ka;
uniform vec3 Kd;
uniform vec3 Ks;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float shininess;    
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform float spotAngle;

uniform sampler2D text;

out vec4 colorFrag;

subroutine vec4 lightProcess(vec3 colorKa, vec3 colorKd);
subroutine uniform lightProcess lightMode;

subroutine (lightProcess)
vec4 Ambient(vec3 colorKa, vec3 colorKd)
{
    vec3 ambient = (Ia * colorKa);
    return vec4(ambient, 1.0);
}

subroutine (lightProcess)
vec4 Point(vec3 colorKa, vec3 colorKd)
{
    vec3 n = normalize(normal);

    vec3 l = normalize(lightPos - position);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (Id * colorKd * max( dot(l, n), 0.0 ) );
    vec3 specular = (Is * Ks * pow( max( dot(r, v), 0.0), shininess));

    return vec4(diffuse + specular, 1.0);
}

subroutine (lightProcess)
vec4 Directional(vec3 colorKa, vec3 colorKd)
{
    vec3 n = normalize(normal);

    vec3 l = -lightDir;
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = Id * colorKd * max( dot(l, n), 0.0 );
    vec3 specular = Is * Ks * pow( max( dot(r, v), 0.0), shininess);

    return vec4(diffuse + specular, 1.0);
}

subroutine (lightProcess)
vec4 Spot(vec3 colorKa, vec3 colorKd)
{
    vec3 l = normalize(lightPos - position);
    vec3 d = lightDir;

    float cosGamma = cos(spotAngle);
    float spotFactor = 1.0;

    if (dot(-l, d) < cosGamma) {
        spotFactor = 0.0; 
    }

    vec3 n = normalize(normal);
    vec3 v = normalize(-position);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (Id * colorKd * max( dot(l, n), 0.0 ) );
    vec3 specular = (Is * Ks * pow( max( dot(r, v), 0.0), shininess) );

    return vec4(spotFactor * (diffuse + specular), 1.0);
}


subroutine vec4 chooseColor();
subroutine uniform chooseColor chosenColor;

subroutine (chooseColor)
vec4 WireframeColor()
{
    return vec4(0, 1, 0, 1);
}

subroutine (chooseColor)
vec4 LightColor()
{
    vec4 light = lightMode(Ka, Kd); 
    return light;
}

subroutine (chooseColor)
vec4 TextureColor()
{
    vec4 color = texture(text, textCoord); 

    vec4 light = lightMode(color.rgb, color.rgb); 
    return light;
}


void main ()
{
    colorFrag = chosenColor();
};