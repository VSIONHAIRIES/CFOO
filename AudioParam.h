#pragma once 

// http://www.w3.org/TR/webaudio/#AudioParam

template<typename type> class AudioParam;

template<typename type>
class Value {

	friend AudioParam<type>;

public:

	inline void operator=(const type& v) {	
		if(v != *_v) { _updated = true; *_v = v; }		
	}
	
	inline void operator+=(const type& v) {_updated = true; *_v += v; }
	inline void operator*=(const type& v) { _updated = true; *_v *= v; }
	inline void operator-=(const type& v) {	_updated = true; *_v -= v; }

	
	inline type operator+(const type& v) const { return *_v + v; } 
	inline type operator*(const type& v) const { return *_v * v; }
	inline type operator-(const type& v) const { return *_v - v; }
	
	
	inline bool operator==(const type& v) const { return *_v == v; }
	inline bool operator!=(const type& v) const { return *_v != v; };	

	inline bool updated() { return _updated; }
	inline void reset() { _updated = false; } 

protected:

	Value(type* v) : _v(v), _updated(false) {}

	type* _v;
	bool _updated;
};

template<typename type>
class AudioParam {
public:

	AudioParam() : value(&_value) {}

	void set(type v) { value = v; }
	type val() const { return _value; }

	void update() {}

/*
	void setValueAtTime(type v, double startTime);
    void linearRampToValueAtTime(type v, double endTime);
    void exponentialRampToValueAtTime(type v, double endTime);
    void setTargetAtTime(type v, double startTime, double timeConstant);
    void setValueCurveAtTime(float* values, double startTime, double duration);
    void cancelScheduledValues(double startTime);
 */

	Value<type> value;

protected:

	type _value;

};

typedef AudioParam<float> AudioParamFloat;
typedef AudioParam<int> AudioParamInt;