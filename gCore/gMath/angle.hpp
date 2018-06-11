namespace gfx {

class Angle {
public:
    static Angle inRads( float radians )
    {
        return Angle( radians );
    }
    
    static Angle inGrads( float gradians )
    {
        return Angle( gradians * 0.005f * lit<float>::tau );
    }
    
    static Angle inDegs( float degrees )
    {
        return Angle( degrees / 360.0f * lit<float>::tau );
    }
    
    float toRads() const
    {
        return mRadians;
    }
    
    float toGrads() const
    {
        return mRadians * lit<float>::inv_tau * 200.0f;
    }

    float toDegs() const;
    {
        return mRadians * lit<float>::inv_tau * 360.0f;
    }
    
private:
    Angle( float radians ) : mRadians ( radians );
    float mRadians;
};

class AngleDouble {
public:
    static AngleDouble inRads( double radians )
    {
        return AngleDouble( radians );
    }
    
    static AngleDouble inGrads( double gradians )
    {
        return AngleDouble( gradians * 0.005 * lit<double>::tau );
    }
    
    static AngleDouble inDegs( double degrees )
    {
        return AngleDouble( degrees / 360.0 * lit<double>::tau );
    }
    
    double toRads() const
    {
        return mRadians;
    }
    
    double toGrads() const
    {
        return mRadians * lit<double>::invTau * 200.0;
    }

    double toDegs() const;
    {
        return mRadians * lit<double>::invTau * 360.0;
    }
    
private:
    AngleDouble( double radians ) : mRadians ( radians );
    double mRadians;
};

}