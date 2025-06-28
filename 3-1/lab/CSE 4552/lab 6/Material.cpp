#include "Material.h"
#include "Hittable.h"
#include "Light.h"
#include "Camera.h"

Color3 Flat::Shade(const HitRecord& rec, const Camera& camera, const std::vector<Light>& lights) const
{
    // Task 1: A Flat material just returns its color
    // 
    // A Flat material is not dependent on either the light or the camera.
    // It is provides its own color without any calculation.
    // ToDo: Update the following return statement to simulate the proper behavior.

    return m_Color;
}

Color3 Lambert::Shade(const HitRecord& rec, const Camera& camera, const std::vector<Light>& lights) const
{
    // Task 2: A Lambert material has only diffused component
    // 
    // Calculate the diffused component with respect to each light source
    // and add them up to the shaded color which is just initialized to be
    // black color. Remember, point light sources can be considered as linear.

    // Shaded color is initialized to all zeros/black.
    Color3 shadedColor{ 0.0, 0.0, 0.0 };

    // This loop iterates over all the lights and adds up shading
    for (const auto& light : lights)
    {

        // ToDo: Perform shading calculation for each light here and add to
        // the shadedColor variable.
        const float dotProduct = blaze::dot(UnitVector(rec.Normal()), UnitVector(light.GetPosition() - rec.P));
        const float negCheck = blaze::max(0, dotProduct);

        shadedColor += m_Color * negCheck *  light.GetIllumination();

    }
    return shadedColor;
}

Color3 Phong::Shade(const HitRecord& rec, const Camera& camera, const std::vector<Light>& lights) const
{
    // Task 3: A Phong material consists of an ambient (just like a flat color), a
    // diffused (Lambertian), and a Phone specular component
    //
    // You need to calculate each of the components separately for each of the lights
    // and add them up in the shadedColor variable.

    Color3 shadedColor{ 0.0, 0.0, 0.0 };

    for (const auto& light : lights)
    {
        const float dotProduct1 = blaze::dot(UnitVector(rec.Normal()), UnitVector(light.GetPosition() - rec.P));
        const float negCheck1 = blaze::max(0, dotProduct1);


        Vec3 ReflecedLight = ReflectAcross(UnitVector(light.GetPosition() - rec.P), rec.Normal()); 
        const float dotProduct2 = blaze::dot(UnitVector( camera.GetOrigin() - rec.P), ReflecedLight );
        const float negCheck2 = blaze::max(0, dotProduct2);

        // ToDo: Perform shading calculation for the ambient color and add with the shadedColor
        const Color3 ambientColor = m_Ambient *  light.GetIllumination();

        // ToDo: Perform shading calculation for the diffused color and add with the shadedColor
        const Color3 diffusedColor = m_Diffused *  negCheck1 * light.GetIllumination();   

        // ToDo: Perform shading calculation for the specular color and add with the shadedColor
        const Color3 specularColor = m_SpecularColor * m_SpecularStrength *  blaze::pow(negCheck2, m_Shininess) * light.GetIllumination();

        shadedColor += ambientColor + diffusedColor + specularColor;
    }

    return shadedColor;
}

Color3 BlinnPhong::Shade(const HitRecord& rec, const Camera& camera, const std::vector<Light>& lights) const
{
    // Task 4: A Blinn-Phong material consists of an ambient (just like a flat color), a
    // diffused (Lambertian), and a Blinn-Phong specular component
    //
    // You need to calculate each of the components separately for each of the lights
    // and add them up in the shadedColor variable. Blinn-Phong material calculation is
    // very similar to the Phong material calculation. Only the specular component calculation
    // is changed to solve some problem/limitations with/of the Phong shading model.

    Color3 shadedColor{ 0.0, 0.0, 0.0 };
    for (const auto& light : lights)
    {
        const float dotProduct1 = blaze::dot(UnitVector(rec.Normal()), UnitVector(light.GetPosition() - rec.P));
        const float negCheck1 = blaze::max(0, dotProduct1);
        

        const float dotProduct2 = blaze::dot(UnitVector( UnitVector(light.GetPosition() - rec.P) + UnitVector(camera.GetOrigin() - rec.P) ), UnitVector(rec.Normal()) );
        const float negCheck2 = blaze::max(0, dotProduct2);
        // ToDo: Perform shading calculation for the ambient color and add with the shadedColor
        const Color3 ambientColor = m_Ambient *  light.GetIllumination();

        // ToDo: Perform shading calculation for the diffused color and add with the shadedColor
        const Color3 diffusedColor = m_Diffused *  negCheck1 * light.GetIllumination();

        // ToDo: Perform shading calculation for the specular color and add with the shadedColor
        const Color3 specularColor = m_SpecularColor * m_SpecularStrength *  blaze::pow(negCheck2, m_Shininess) * light.GetIllumination();

        shadedColor += ambientColor + diffusedColor + specularColor;
    }
    return shadedColor;
}
