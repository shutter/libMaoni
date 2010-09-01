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

#ifndef QVECTOR4DPROPERTYMANAGER_HPP
#define QVECTOR4DPROPERTYMANAGER_HPP

#include <qtpropertybrowser.h>
#include <qtpropertymanager.h>
#include <Maoni/Vector.hpp>

class QVector4DPropertyManagerPrivate;

class QVector4DPropertyManager: public QtAbstractPropertyManager
{
Q_OBJECT

public:
	QVector4DPropertyManager(QObject* parent = 0);
	~QVector4DPropertyManager();

	QtDoublePropertyManager* subDoublePropertyManager() const;

	Vec4 value(const QtProperty* property) const;
	int decimals(const QtProperty* property) const;

public Q_SLOTS:
	void setValue(QtProperty* property, const Vec4 &val);
	void setDecimals(QtProperty* property, int prec);

Q_SIGNALS:
	void valueChanged(QtProperty* property, const Vec4 &val);
	void decimalsChanged(QtProperty* property, int prec);

protected:
	QString valueText(const QtProperty* property) const;
	virtual void initializeProperty(QtProperty* property);
	virtual void uninitializeProperty(QtProperty* property);

private:
	QVector4DPropertyManagerPrivate *d_ptr;
	Q_DECLARE_PRIVATE(QVector4DPropertyManager)
	Q_DISABLE_COPY(QVector4DPropertyManager)
	Q_PRIVATE_SLOT(d_func(), void slotDoubleChanged(QtProperty*, double))
	Q_PRIVATE_SLOT(d_func(), void slotPropertyDestroyed(QtProperty*))
};

#endif /* QVECTOR4DPROPERTYMANAGER_HPP */
