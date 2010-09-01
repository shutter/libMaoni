/*
 * libMaoni common viewing framework
 * Copyright (C) 2009, 2010 Daniel Pfeifer
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qvector2dpropertymanager.h"
#include <QMap>
#include <boost/la/all.hpp>
using namespace boost::la;

template<class Value, class PrivateData>
static Value getData(const QMap<const QtProperty *, PrivateData> &propertyMap,
	Value PrivateData::*data, const QtProperty *property,
	const Value &defaultValue = Value())
{
	typedef QMap<const QtProperty *, PrivateData> PropertyToData;
	typedef Q_TYPENAME PropertyToData::const_iterator PropertyToDataConstIterator;
	const PropertyToDataConstIterator it = propertyMap.constFind(property);
	if (it == propertyMap.constEnd())
	return defaultValue;
	return it.value().*data;
}

template<class Value, class PrivateData>
static Value getValue(const QMap<const QtProperty *, PrivateData> &propertyMap,
	const QtProperty *property, const Value &defaultValue = Value())
{
	return getData<Value> (propertyMap, &PrivateData::val, property,
		defaultValue);
}

class QVector2DPropertyManagerPrivate
{
	QVector2DPropertyManager* q_ptr;
	Q_DECLARE_PUBLIC(QVector2DPropertyManager)

public:
	struct Data
	{
		Data() :
			decimals(2)
		{
		}

		Vec2 val;
		int decimals;
	};

	void slotDoubleChanged(QtProperty* property, double value);
	void slotPropertyDestroyed(QtProperty* property);

	typedef QMap<const QtProperty*, Data> PropertyValueMap;
	PropertyValueMap m_values;

	QtDoublePropertyManager *m_doublePropertyManager;

	QMap<const QtProperty*, QtProperty*> m_propertyToX;
	QMap<const QtProperty*, QtProperty*> m_propertyToY;

	QMap<const QtProperty*, QtProperty*> m_xToProperty;
	QMap<const QtProperty*, QtProperty*> m_yToProperty;
};

void QVector2DPropertyManagerPrivate::slotDoubleChanged(QtProperty* property,
	double value)
{
	if (QtProperty *prop = m_xToProperty.value(property, 0))
	{
		Vec2 p = m_values[prop].val;
		p | X = value;
		q_ptr->setValue(prop, p);
	}
	else if (QtProperty *prop = m_yToProperty.value(property, 0))
	{
		Vec2 p = m_values[prop].val;
		p | Y  = value;
		q_ptr->setValue(prop, p);
	}
}

void QVector2DPropertyManagerPrivate::slotPropertyDestroyed(
	QtProperty *property)
{
	if (QtProperty *pointProp  = m_xToProperty.value(property, 0))
	{
		m_propertyToX[pointProp] = 0;
		m_xToProperty.remove(property);
	}
	else if (QtProperty *pointProp = m_yToProperty.value(property, 0))
	{
		m_propertyToY[pointProp] = 0;
		m_yToProperty.remove(property);
	}
}

QVector2DPropertyManager::QVector2DPropertyManager(QObject *parent) :
	QtAbstractPropertyManager(parent)
{
	d_ptr = new QVector2DPropertyManagerPrivate;
	d_ptr->q_ptr = this;

	d_ptr->m_doublePropertyManager = new QtDoublePropertyManager(this);
	connect(d_ptr->m_doublePropertyManager,
		SIGNAL(valueChanged(QtProperty *, double)), //
		this, SLOT(slotDoubleChanged(QtProperty *, double)));
	connect(d_ptr->m_doublePropertyManager,
		SIGNAL(propertyDestroyed(QtProperty *)), //
		this, SLOT(slotPropertyDestroyed(QtProperty *)));
}

QVector2DPropertyManager::~QVector2DPropertyManager()
{
	clear();
	delete d_ptr;
}

QtDoublePropertyManager *QVector2DPropertyManager::subDoublePropertyManager() const
{
	return d_ptr->m_doublePropertyManager;
}

Vec2 QVector2DPropertyManager::value(const QtProperty *property) const
{
	return getValue<Vec2> (d_ptr->m_values, property);
}

int QVector2DPropertyManager::decimals(const QtProperty *property) const
{
	return getData<int> (d_ptr->m_values,
		&QVector2DPropertyManagerPrivate::Data::decimals, property, 0);
}

QString QVector2DPropertyManager::valueText(const QtProperty *property) const
{
	const QVector2DPropertyManagerPrivate::PropertyValueMap::const_iterator it =
		d_ptr->m_values.constFind(property);
	if (it == d_ptr->m_values.constEnd())
		return QString();
	const Vec2 v = it.value().val;
	const int dec = it.value().decimals;
	return QString(tr("(%1, %2)") //
		.arg(QString::number(v | X , 'f', dec)) //
		.arg(QString::number(v | Y , 'f', dec)));
}

void QVector2DPropertyManager::setValue(QtProperty *property,
	const Vec2 &val)
{
	const QVector2DPropertyManagerPrivate::PropertyValueMap::iterator it =
		d_ptr->m_values.find(property);
	if (it == d_ptr->m_values.end())
		return;

	if (it.value().val == val)
		return;

	it.value().val = val;
	d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToX[property],
		val|X);
	d_ptr->m_doublePropertyManager->setValue(d_ptr->m_propertyToY[property],
		val|Y);

	emit propertyChanged(property);
	emit valueChanged(property, val);
}

void QVector2DPropertyManager::setDecimals(QtProperty *property, int prec)
{
	const QVector2DPropertyManagerPrivate::PropertyValueMap::iterator it =
		d_ptr->m_values.find(property);
	if (it == d_ptr->m_values.end())
		return;

	QVector2DPropertyManagerPrivate::Data data = it.value();

	if (prec > 13)
		prec = 13;
	else if (prec < 0)
		prec = 0;

	if (data.decimals == prec)
		return;

	data.decimals = prec;
	d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToX[property],
		prec);
	d_ptr->m_doublePropertyManager->setDecimals(d_ptr->m_propertyToY[property],
		prec);

	it.value() = data;

	emit decimalsChanged(property, data.decimals);
}

void QVector2DPropertyManager::initializeProperty(QtProperty *property)
{
	d_ptr->m_values[property] = QVector2DPropertyManagerPrivate::Data();

	QtProperty *xProp = d_ptr->m_doublePropertyManager->addProperty();
	xProp->setPropertyName(tr("X"));
	d_ptr->m_doublePropertyManager->setDecimals(xProp, decimals(property));
	d_ptr->m_doublePropertyManager->setValue(xProp, 0);
	d_ptr->m_propertyToX[property] = xProp;
	d_ptr->m_xToProperty[xProp] = property;
	property->addSubProperty(xProp);

	QtProperty *yProp = d_ptr->m_doublePropertyManager->addProperty();
	yProp->setPropertyName(tr("Y"));
	d_ptr->m_doublePropertyManager->setDecimals(yProp, decimals(property));
	d_ptr->m_doublePropertyManager->setValue(yProp, 0);
	d_ptr->m_propertyToY[property] = yProp;
	d_ptr->m_yToProperty[yProp] = property;
	property->addSubProperty(yProp);
}

void QVector2DPropertyManager::uninitializeProperty(QtProperty *property)
{
	QtProperty *xProp = d_ptr->m_propertyToX[property];
	if (xProp)
	{
		d_ptr->m_xToProperty.remove(xProp);
		delete xProp;
	}
	d_ptr->m_propertyToX.remove(property);

	QtProperty *yProp = d_ptr->m_propertyToY[property];
	if (yProp)
	{
		d_ptr->m_yToProperty.remove(yProp);
		delete yProp;
	}
	d_ptr->m_propertyToY.remove(property);

	d_ptr->m_values.remove(property);
}

#include "moc_qvector2dpropertymanager.cpp"
//#include "qtpropertymanager.moc"
