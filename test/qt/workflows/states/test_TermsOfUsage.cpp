/*!
 * \brief Tests the Terms of Usage of CertificateDescription
 *
 * \copyright Copyright (c) 2014-2020 Governikus GmbH & Co. KG, Germany
 */

#include "asn1/CertificateDescription.h"

#include "TestFileHelper.h"

#include <QtTest>

using namespace governikus;

class test_TermsOfUsage
	: public QObject
{
	Q_OBJECT

	private Q_SLOTS:
		void testPurposeOf_2014_07_03_cvcDescription_data()
		{
			QTest::addColumn<QString>("purpose");

			QTest::newRow("0") << QStringLiteral("- Anmeldung und Registrierung im Portal der Bundesagentur f\u00FCr Arbeit (BA) f\u00FCr Gesch\u00E4ftsvorf\u00E4lle, die im Portal der BA verf\u00FCgbar sind -");
			QTest::newRow("1") << QStringLiteral("- Authentisierung der Studierenden beim Login an Hochschuldiensten -");
			QTest::newRow("2") << QStringLiteral("Registrierung / Login f\u00FCr \"Meine TK\"");
			QTest::newRow("3") << QStringLiteral("Permanentes B\u00FCrgerkonto");
			QTest::newRow("4") << QStringLiteral("- Selbstauskunft -");
			QTest::newRow("5") << QStringLiteral("- Registrierung und Login f\u00FCr ein Benutzerkonto im HamburgService -");
			QTest::newRow("6") << QStringLiteral("- Altersverifikation f\u00FCr Online-Shop- und eCommerce-Anbieter per Web-Schnittstelle -");
			QTest::newRow("7") << QStringLiteral("- Abwicklung von Verwaltungsleistungen mit Identifikationsbedarf ohne Registrierung -");
			QTest::newRow("8") << QStringLiteral("Abwicklung von Verwaltungsleistungen ohne Registrierung");
			QTest::newRow("9") << QStringLiteral("- Tempor\u00E4res B\u00FCrgerkonto -");
			QTest::newRow("10") << QStringLiteral("- Tempor\u00E4res B\u00FCrgerkonto -");
			QTest::newRow("11") << QStringLiteral("- Online Bearbeitung f\u00FCr Antr\u00E4ge nach dem SGB IX -");
			QTest::newRow("12") << QStringLiteral("- Tempor\u00E4res B\u00FCrgerkonto -");
			QTest::newRow("13") << QStringLiteral("BONIGO");
			QTest::newRow("14") << QStringLiteral("Registrierung / Login f\u00FCr \"meinCosmosDirekt\"");
			QTest::newRow("15") << QStringLiteral("- Selbstauskunft -");
			QTest::newRow("16") << QStringLiteral("- Login B\u00FCrgerkonto \"Mein Hagen\" -");
			QTest::newRow("17") << QStringLiteral("- Verifikation von Personendaten zur Alters- und Identit\u00E4tsfeststellung -");
			QTest::newRow("18") << QStringLiteral("- Registrierung f\u00FCr die Virtuelle Poststelle bei der Deutschen Emissionshandelsstelle -");
		}


		void testPurposeOf_2014_07_03_cvcDescription()
		{
			QFETCH(QString, purpose);

			const auto& filename = QStringLiteral(":/core/step/2014_07_03_cvcDescription%1.bin").arg(QString::fromLatin1(QTest::currentDataTag()));
			QSharedPointer<const CertificateDescription> certDescr = CertificateDescription::fromHex(TestFileHelper::readFile(filename).toHex());
			QVERIFY(certDescr);
			QCOMPARE(certDescr->getPurpose(), purpose);
		}


		void testPurpose_data()
		{
			QTest::addColumn<QByteArray>("hex");
			QTest::addColumn<QString>("purpose");

			QTest::newRow("DescTestAutentServer")
				<< QByteArray("3082022F060A04007F00070301030101A12D0C2B446575747363686520506F737420436F6D2C204765736368C3A466747366656C64205369676E7472757374A2191317687474703A2F2F7777772E7369676E74727573742E6465A3080C06626F73204B47A429132768747470733A2F2F6465762D64656D6F2E676F7665726E696B75732D6569642E64653A38343433A58201580C820154416E736368726966743A0D0A6272656D656E206F6E6C696E6520736572766963657320476D6248202620436F2E204B470D0A416D2046616C6C7475726D20390D0A3238333539204272656D656E0D0A0D0A452D4D61696C2D416472657373653A0D0A686240626F732D6272656D656E2E64650D0A0D0A5A7765636B20646573204175736C657365766F7267616E67733A0D0A44656D6F6E7374726174696F6E20646573206549442D536572766963650D0A0D0A5A757374C3A46E6469676520446174656E73636875747A61756673696368743A0D0A446965204C616E64657362656175667472616774652066C3BC7220446174656E73636875747A20756E6420496E666F726D6174696F6E736672656968656974206465722046726569656E2048616E73657374616474204272656D656E0D0A41726E647473747261C39F6520310D0A3237353730204272656D6572686176656EA74631440420761099A58BFD5334E93A7A78E4F18B760FFCF8F513A4730C8AE9B59BCC0FE8C90420CEABB7E427174BCFFFB3499BF925A5D4A7887AD4FCF7747867912DEBB58D684C")
				<< QStringLiteral("Demonstration des eID-Service");

			QTest::newRow("DescRlpDirektServer")
				<< QByteArray("30820312060A04007F00070301030101A10E0C0C442D547275737420476D6248A2181316687474703A2F2F7777772E642D74727573742E6E6574A33E0C3C4B6F6D6D5769732D476573656C6C73636861667420662E204B6F6D6D756E696B6174696F6E20752E2057697373656E737472616E73666572206D6248A416131468747470733A2F2F74626B2E65776F69732E6465A58201F20C8201EEEFBBBF4E616D652C20416E7363687269667420756E6420452D4D61696C2D4164726573736520646573204469656E7374616E626965746572733A0D0A4B6F6D6D5769732D476573656C6C73636861667420662E204B6F6D6D756E696B6174696F6E20752E2057697373656E737472616E73666572206D62480D0A48696E64656E62757267706C61747A20330D0A3535313138204D61696E7A0D0A737570706F7274406B6F6D6D7769732E64650D0A0D0A4765736368C3A46674737A7765636B3A0D0A41627769636B6C756E6720766F6E2056657277616C74756E67736C65697374756E67656E206D6974204964656E746966696B6174696F6E73626564617266206F686E652052656769737472696572756E6720696D2053696E6E65206465722047656D4F20526865696E6C616E642D5066616C7A0D0A0D0A5A757374C3A46E6469676520446174656E73636875747A626568C3B67264653A0D0A4175667369636874732D20756E64204469656E73746C65697374756E6773646972656B74696F6E2028414444290D0A54726965720D0A57696C6C792D4272616E64742D506C61747A20330D0A35343239302054726965720D0A303635312F393439342D300D0A706F73747374656C6C65406164642E726C702E64650D0A7777772E646174656E73636875747A2E726C702E6465A7818B31818804205B100843E6D2569F2FB5108A2D327D1929ED7EC814531D014B84C2B76B67FE6904209D8EB0BDF36B19C4AF3147E57401FD792845F0413102A7BD784DF9418098BEBE0420DB37C8E02D6D715EFBFB819D9620C0D411BB6D5F8000200148FFCFA3467F71580420EBD2A9610AA53AE1C159B2C7B238451E2C6AF06F7034723BD4B9743196E6A720")
				<< QStringLiteral("Abwicklung von Verwaltungsleistungen mit Identifikationsbedarf ohne Registrierung im Sinne der GemO Rheinland-Pfalz");

			QTest::newRow("DescAgetoServer")
				<< QByteArray("3082029E060A04007F00070301030101A1140C12414745544F205365727669636520476D6248A2161314687474703A2F2F7777772E616765746F2E6E6574A3170C15414745544F20496E6E6F766174696F6E20476D6248A421131F68747470733A2F2F6569642E73657276696365732E616765746F2E6E65742FA58201DC0C8201D84E616D652C20416E7363687269667420756E6420452D4D61696C2D4164726573736520646573204469656E7374616E626965746572733A0A414745544F20496E6E6F766174696F6E20476D62480A57696E7A65726C616572205374722E20320A3037373435204A656E610A6E706140616765746F2E6E65740A0A5A7765636B2064657220446174656EC3BC6265726D6974746C756E673A0A4964656E746966697A696572756E6720756E642052656769737472696572756E67207A756D2070657273C3B66E6C696368656E204B756E64656E6B6F6E746F0A0A5A757374C3A46E6469676520446174656E73636875747A626568C3B67264653A0A5468C3BC72696E676572204C616E64657376657277616C74756E6773616D740A5265666572617420486F6865697473616E67656C6567656E68656974656E2C20476566616872656E6162776568720A5765696D6172706C61747A20340A3939343233205765696D61720A0A54656C3A20283033203631292033372037332037322035380A4661783A20283033203631292033372037332037332034360A706F73747374656C6C6540746C7677612E7468756572696E67656E2E64650A416E737072656368706172746E65723A204672617520416E6B65204E65756D616E6EA746314404202E78EBFA001EE9D9F02CCE6B5D93535FC8492FA634BE5BDD679EF430C73864000420D9D682F644CDC3685747104A7CA7C1B3302D81D2A17A88607143F664BF23FF90")
				<< QStringLiteral("Identifizierung und Registrierung zum pers\u00F6nlichen Kundenkonto");

			QTest::newRow("Empty Purpose")
				<< QByteArray("30820322060a04007f00070301030101a10e0c0c442d547275737420476d6248a2181316687474703a2f2f7777772e642d74727573742e6e6574a3460c444d696e697374657269756d2066c3bc7220576972747363686166742c20496e6e6f766174696f6e2c204469676974616c6973696572756e6720756e6420456e6572676965a41a131868747470733a2f2f736572766963656b6f6e746f2e6e7277a582021a0c8202164e616d652c20416e7363687269667420756e6420452d4d61696c2d4164726573736520646573204469656e737465616e626965746572733a0d0a4d696e697374657269756d2066c3bc7220576972747363686166742c20496e6e6f766174696f6e2c204469676974616c6973696572756e6720756e6420456e65726769650d0a46726965647269636873747261c39f652036322d38300d0a34303231372044c3bc7373656c646f72660d0a706f73747374656c6c65406d776964652e6e72772e64650d0a0d0a4765736368c3a46674737a7765636b3a0d0a0d0a48696e7765697320617566206469652066c3bc722064656e204469656e737465616e626965746572207a757374c3a46e646967656e205374656c6c656e2c20646965206469652045696e68616c74756e672064657220566f7273636872696674656e207a756d20446174656e73636875747a206b6f6e74726f6c6c696572656e3a0d0a4c616e64657362656175667472616774652066c3bc7220446174656e73636875747a20756e6420496e666f726d6174696f6e736672656968656974204e6f7264726865696e2d0d0a5765737466616c656e0d0a4b6176616c6c6572696573747261c39f6520322d340d0a34303231332044c3bc7373656c646f72660d0a30322031312f3338342032342d300d0a706f73747374656c6c65406c64692e6e72772e64650d0a687474703a2f2f7777772e6c64692e6e72772e6465a768316604204ae5b7dada1346040ebf351b00399f4c0228a771aa128ba74c8b1c23273247e60420883bc461526a4e08e99603f8d41c60ad7cf4711fe1662975e797e816885770650420dadadde7a189cbb7c5f78a77ae5e22f61e646e5d3ce9005d0cbf4b581cdacd4e")
				<< QString();
		}


		void testPurpose()
		{
			QFETCH(QByteArray, hex);
			QFETCH(QString, purpose);

			QSharedPointer<const CertificateDescription> certDescr = CertificateDescription::fromHex(hex);
			QVERIFY(certDescr);
			QCOMPARE(certDescr->getPurpose(), purpose);
		}


};

QTEST_GUILESS_MAIN(test_TermsOfUsage)
#include "test_TermsOfUsage.moc"