/*******************************************************************************
Copyright (c) 2012-2016 Alex Zhondin <lexxmark.dev@gmail.com>
Copyright (c) 2015-2019 Alexandra Cherdantseva <neluhus.vagus@gmail.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*******************************************************************************/

#include "PropertyEnum.h"

QtnPropertyEnumBase::QtnPropertyEnumBase(QObject *parent)
	: QtnSinglePropertyBase<QtnEnumValueType>(parent)
	, m_enumInfo(nullptr)
{
}

bool QtnPropertyEnumBase::fromStrImpl(
	const QString &str, QtnPropertyChangeReason reason)
{
	if (!m_enumInfo)
		return false;

	const QtnEnumValueInfo *enumValue = m_enumInfo->fromStr(str);

	if (!enumValue)
		return false;

	return setValue(enumValue->value(), reason);
}

bool QtnPropertyEnumBase::toStrImpl(QString &str) const
{
	if (!m_enumInfo)
		return false;

	QtnEnumValueType v = value();
	const QtnEnumValueInfo *enumValue = m_enumInfo->findByValue(v);
	return m_enumInfo->toStr(str, enumValue);
}

bool QtnPropertyEnumBase::isValueAcceptedImpl(ValueType valueToAccept)
{
	if (!m_enumInfo)
		return false;

	if (!m_enumInfo->findByValue(valueToAccept))
		return false;

	return true;
}

QtnPropertyEnumCallback::QtnPropertyEnumCallback(QObject *parent)
	: QtnSinglePropertyCallback<QtnPropertyEnumBase>(parent)
{
}

QtnPropertyEnum::QtnPropertyEnum(QObject *parent)
	: QtnSinglePropertyValue<QtnPropertyEnumBase>(parent)
{
}
