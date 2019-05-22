/*!
 * \copyright Copyright (c) 2017-2019 Governikus GmbH & Co. KG, Germany
 */

#include "RemoteDeviceDescriptor.h"

#include "messages/Discovery.h"

#include <QtTest/QtTest>


using namespace governikus;


class test_RemoteDeviceDescriptor
	: public QObject
{
	Q_OBJECT

	private:
		quint16 mPort;

	private Q_SLOTS:
		void initTestCase()
		{
			mPort = 0;
		}


		void testValidDescriptorIsEqualToItself()
		{
			const Discovery validMsg(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0});
			const QHostAddress address(QHostAddress::LocalHost);
			const RemoteDeviceDescriptor valid(validMsg, address);

			QVERIFY(valid == valid);
		}


		void testDistinctInvalidDescriptorsAreEqual()
		{
			const QHostAddress address1(QStringLiteral("192.168.1.1"));
			const QHostAddress address2(QHostAddress::LocalHost);

			const RemoteDeviceDescriptor invalid1(Discovery(QJsonObject()), address1);
			const RemoteDeviceDescriptor invalid2(Discovery(QJsonObject()), address2);

			QVERIFY(invalid1 == invalid2);
		}


		void testValidDescriptorIsDifferentFromInvalid()
		{
			const Discovery validMsg(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0});
			const Discovery invalidMsg("", "", 0, {});
			const QHostAddress address(QHostAddress::LocalHost);

			const RemoteDeviceDescriptor valid(validMsg, address);
			const RemoteDeviceDescriptor invalid(invalidMsg, address);

			QVERIFY(!(valid == invalid));
		}


		void testDistinctValidDescriptorsWithDifferentDataAreDifferent()
		{
			const Discovery validMsg1(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0});
			const Discovery validMsg2(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0, IfdVersion::Version::v_test});
			const QHostAddress address(QHostAddress::LocalHost);

			const RemoteDeviceDescriptor valid1(validMsg1, address);
			const RemoteDeviceDescriptor valid2(validMsg2, address);

			QVERIFY(!(valid1 == valid2));
		}


		void testDistinctValidDescriptorsWithTheSameDataAreEqual()
		{
			const Discovery validMsg1(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0});
			const Discovery validMsg2(QStringLiteral("Device"), QStringLiteral("0123456789ABCDEF"), mPort, {IfdVersion::Version::v0});
			const QHostAddress address(QHostAddress::LocalHost);

			const RemoteDeviceDescriptor valid1(validMsg1, address);
			const RemoteDeviceDescriptor valid2(validMsg2, address);

			QVERIFY(valid1 == valid2);
		}


};

QTEST_GUILESS_MAIN(test_RemoteDeviceDescriptor)
#include "test_RemoteDeviceDescriptor.moc"
