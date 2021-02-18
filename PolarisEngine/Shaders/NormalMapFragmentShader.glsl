#version 410

in vec3 tangentPos;
in vec2 textCoord;

in vec3 lightPosTangent;
in vec3 lightDirTangent;

uniform vec3 Ks;

uniform vec3 Ia;
uniform vec3 Id;
uniform vec3 Is;
uniform float shininess;    
uniform float spotAngle;

uniform sampler2D text;
uniform sampler2D normalText;

out vec4 colorFrag;

subroutine vec4 lightProcess(vec3 colorKa, vec3 colorKd, vec4 normal);
subroutine uniform lightProcess lightMode;

subroutine (lightProcess)
vec4 Ambient(vec3 colorKa, vec3 colorKd, vec4 normal)
{
    vec3 ambient = (Ia * colorKa);
    return vec4(ambient, 1.0);
}

subroutine (lightProcess)
vec4 Point(vec3 colorKa, vec3 colorKd, vec4 normal)
{
    vec3 n = normalize(normal.rgb);

    vec3 l = normalize(lightPosTangent - tangentPos);
    vec3 v = normalize(-tangentPos);
    vec3 r = reflect(-l, n);

    vec3 diffuse = (Id * colorKd * max( dot(l, n), 0.0 ) );
    vec3 specular = (Is * Ks * pow( max( dot(r, v), 0.0), shininess));

    return vec4(diffuse + specular, 1.0);
}

subroutine (lightProcess)
vec4 Directional(vec3 colorKa, vec3 colorKd, vec4 normal)
{
    vec3 n = normalize(normal.rgb);

    vec3 l = normalize(-lightDirTangent);
    vec3 v = normalize(-tangentPos);
    vec3 r = reflect(-l, n);

    vec3 diffuse = Id * colorKd * max( dot(l, n), 0.0 );
    vec3 specular = Is * Ks * pow( max( dot(r, v), 0.0), shininess);

    return vec4(diffuse + specular, 1.0);
}

subroutine (lightProcess)
vec4 Spot(vec3 colorKa, vec3 colorKd, vec4 normal)
{
    vec3 l = normalize(lightPosTangent - tangentPos);
    vec3 d = normalize(lightDirTangent);

    float cosGamma = cos(spotAngle);
    float spotFactor = 1.0;

    if (dot(-l, d) < cosGamma) {
        spotFactor = 0.0; 
    }

    vec3 n = normalize(normal.rgb);
    vec3 v = -tangentPos;
    vec3 r = reflect(-l, n);

    vec3 diffuse = (Id * colorKd * max( dot(l, n), 0.0 ) );
    vec3 specular = (Is * Ks * pow( max( dot(r, v), 0.0), shininess) );

    return vec4(spotFactor * (diffuse + specular), 1.0);
}

subroutine vec4 chooseColor();
subroutine uniform chooseColor chosenColor;

subroutine (chooseColor)
vec4 TextureColor()
{
    vec4 normal = 2.0 * (texture(normalText, textCoord) - 0.5); 
    vec4 color = texture(text, textCoord);

    vec4 light = lightMode(color.rgb, color.rgb, normal); 
    return light;
}

void main ()
{
    colorFrag = chosenColor();
};