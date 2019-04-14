#include "pch.h"
#include "../ISpringWord/AddImageCommand.h"
#include "../ISpringWord/Document.h"
#include "../ISpringWord/History.h"
#include "../ISpringWord/Image.h"
#include "../ISpringWord/Menu.h"
#include "../ISpringWord/Paragraph.h"
#include "../ISpringWord/TextAndImageEditor.h"
#include "ConstPath.h"

CDocument document;
class CEditorList
{
public:
	CEditorList(){};

	void List(std::ostream& strstm, CDocument* m_document)
	{
		strstm << "Title: " << m_document->GetTitle() << std::endl;
		auto itemsCount = m_document->GetItemsCount();

		for (size_t i = 0; i < itemsCount; ++i)
		{
			strstm << i << ". ";
			auto item = m_document->GetItem(i);

			if (auto text = item.GetParagraph())
			{
				strstm << "Paragraph: " << text->GetText() << std::endl;
			}

			if (auto image = item.GetImage())
			{
				strstm << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << std::endl;
			}
		}
	}
};

TEST_CASE("Can set title")
{
	CDocument document;
	std::string title = "<!--test-->";
	document.SetTitle(title);
	REQUIRE(document.GetTitle() == title);
}

TEST_CASE("Can insert paragraph", "[CDocument]")
{
	std::string text = "test";
	document.InsertParagraph(text, 0);
	std::string str = "Title: \n0. Paragraph: test\n";
	std::stringstream strstm;
	std::stringstream strstmList;
	strstm << str;
	CEditorList editor;
	editor.List(strstmList, &document);
	REQUIRE(strstmList.str() == strstm.str());
}

TEST_CASE("Can insert image")
{
	document.Delete(0);
	CEditorList editor;
	std::string path = (PATH + "image.png");
	boost::algorithm::trim_left(path);
	const boost::filesystem::path imgPath = boost::filesystem::path(path);
	document.InsertImage(imgPath, 100, 100, 0);
	auto img = document.GetItem(0).GetImage();

	std::stringstream strstm;
	strstm << "Title: \n0. Image: " << img->GetWidth() << " " << img->GetHeight() << " \"" << img->GetPath().string() << "\"\n";
	std::stringstream strstmList;
	editor.List(strstmList, &document);
	REQUIRE(strstmList.str() == strstm.str());
}

TEST_CASE("Can not insert image with wrong path")
{
	std::string path = (PATH + "image/" + "image.png");
	boost::algorithm::trim_left(path);
	const boost::filesystem::path imgPath = boost::filesystem::path(path);

	REQUIRE_THROWS(document.InsertImage(imgPath, 100, 100, 0));
}

TEST_CASE("Can not insert image with wrong extension")
{
	std::string path = boost::filesystem::change_extension(PATH + "image.png", ".doc").string();
	boost::algorithm::trim_left(path);
	const boost::filesystem::path imgPath = boost::filesystem::path(path);

	REQUIRE_THROWS(document.InsertImage(imgPath, 100, 100, 0));
}

TEST_CASE("Can get item")
{
	CEditorList editor;
	auto img = document.GetItem(0).GetImage();

	std::stringstream strstm;
	strstm << "Title: \n0. Image: " << img->GetWidth() << " " << img->GetHeight() << " \"" << img->GetPath().string() << "\"\n";
	std::stringstream strstmList;
	editor.List(strstmList, &document);
	REQUIRE(strstmList.str() == strstm.str());
	REQUIRE(strstmList.str() == strstm.str());
}

TEST_CASE("Can get items count")
{
	std::string text = "test";
	document.InsertParagraph(text, 0);
	REQUIRE(document.GetItemsCount() == 2);
}

TEST_CASE("Can undo command [DocumentTest]")
{
	std::string title = "test";
	document.SetTitle(title);
	document.Undo();
	REQUIRE(document.GetTitle() == "");
}

TEST_CASE("Can redo command [DocumentTest]")
{
	std::string title = "test";
	document.SetTitle(title);
	document.Undo();
	REQUIRE(document.GetTitle() == "");
	document.Redo();
	REQUIRE(document.GetTitle() == "test");
}

TEST_CASE("Can delete item")
{
	std::string text = "test";
	REQUIRE(document.GetItemsCount() == 2);
	document.Delete(0);
	REQUIRE(document.GetItemsCount() == 1);
}

TEST_CASE("Can save file")
{
	boost::filesystem::remove(PATH + "test.html");
	REQUIRE_FALSE(boost::filesystem::exists(PATH + "test.html"));
	std::string text = "test";
	document.InsertParagraph(text, 0);
	document.Save(PATH + "test.html");
	REQUIRE(boost::filesystem::exists(PATH + "test.html"));
	boost::system::error_code errorCode;
	boost::filesystem::remove(PATH + "test.html", errorCode);
	if (errorCode)
	{
		std::cout << errorCode.message() << std::endl;
	}
}

TEST_CASE("Can not save with wrong escapes")
{
	std::string text = "test";
	CDocument document;
	document.InsertParagraph(text, 0);

	document.Save(PATH + "test.html");
	std::ifstream ifs(PATH + "test.html");
	std::stringstream buffer;

	buffer << ifs.rdbuf();

	std::stringstream str;

	str << "<html>" << std::endl;
	str << "<head>" << std::endl;
	str << "<title></title>" << std::endl;
	str << "</head>" << std::endl;
	str << "<body>" << std::endl;
	str << "<p>test</p>" << std::endl;
	str << "</body>" << std::endl;
	str << "</html>" << std::endl;

	REQUIRE(buffer.str() == str.str());
}
