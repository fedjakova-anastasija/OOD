#include <boost/format.hpp>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

namespace graphics_lib_pro
{
// Холст для рисования
class ICanvas
{
public:
	// Установка цвета в формате 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		// TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
		cout << "SetColor (#" << hex << uppercase << rgbColor << std::dec  << ")" << endl;
	}

	void MoveTo(int x, int y) override
	{
		// Реализация остается без изменения
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		// Реализация остается без изменения
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
} // namespace graphics_lib_pro

// Пространство имен библиотеки для рисования фигур (использует graphics_lib_pro)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
struct Point
{
	int x;
	int y;
};

// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib_pro
class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib_pro::ICanvas& canvas) const = 0;
	virtual ~ICanvasDrawable() = default;
};

class CTriangle : public ICanvasDrawable
{
public:
	CTriangle(const Point& p1, const Point& p2, const Point& p3, uint32_t rgbColor)
		: m_vertex1(p1)
		, m_vertex2(p2)
		, m_vertex3(p3)
		, m_rgbColor(rgbColor)
	{
		// TODO: написать код конструктора
	}

	void Draw(graphics_lib_pro::ICanvas& canvas) const override
	{
		// TODO: написать код рисования треугольника на холсте
		canvas.SetColor(m_rgbColor);
		canvas.MoveTo(m_vertex1.x, m_vertex1.y);

		canvas.LineTo(m_vertex2.x, m_vertex2.y);
		canvas.LineTo(m_vertex3.x, m_vertex3.y);
		canvas.LineTo(m_vertex1.x, m_vertex1.y);
	}

private:
	// TODO: дописать приватную часть
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
	uint32_t m_rgbColor;
};

class CRectangle : public ICanvasDrawable
{
public:
	CRectangle(const Point& leftTop, int width, int height, uint32_t rgbColor)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_rgbColor(rgbColor)
	{
		// TODO: написать код конструктора
	}

	void Draw(graphics_lib_pro::ICanvas& canvas) const override
	{
		// TODO: написать код рисования прямоугольника на холсте
		canvas.SetColor(m_rgbColor);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);

		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

private:
	// TODO: дописать приватную часть
	Point m_leftTop;
	int m_width;
	int m_height;
	uint32_t m_rgbColor;
};

// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
class CCanvasPainter
{
public:
	CCanvasPainter(graphics_lib_pro::ICanvas& canvas)
		: m_canvas(canvas)
	{
		// TODO: дописать конструктор класса
	}
	void Draw(const ICanvasDrawable& drawable)
	{
		// TODO: дописать код рисования ICanvasDrawable на canvas, переданном в конструктор
		drawable.Draw(m_canvas);
	}

private:
	// TODO: дописать приватную часть
	graphics_lib_pro::ICanvas& m_canvas;
};
} // namespace shape_drawing_lib

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
class CPoint
{
public:
	CPoint(int x, int y)
		: x(x)
		, y(y)
	{
	}

	int x;
	int y;
};

// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
class CRGBAColor
{
public:
	CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{
	}
	float r, g, b, a;
};

// Класс для современного рисования графики
class CModernGraphicsRenderer
{
public:
	CModernGraphicsRenderer(ostream& strm)
		: m_out(strm)
	{
	}

	~CModernGraphicsRenderer()
	{
		// Реализация остается без изменения
		if (m_drawing) // Завершаем рисование, если оно было начато
		{
			EndDraw();
		}
	}

	// Этот метод должен быть вызван в начале рисования
	void BeginDraw()
	{
		// Реализация остается без изменения
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	// Выполняет рисование линии
	void DrawLine(const CPoint& start, const CPoint& end, const CRGBAColor& rgbColor)
	{
		// TODO: выводит в output инструкцию для рисования линии в виде
		// <line fromX="3" fromY="5" toX="5" toY="17">
		//   <color r="0.35" g="0.47" b="1.0" a="1.0" />
		// </line>
		// Можно вызывать только между BeginDraw() и EndDraw()
		if (!m_drawing)
		{
			throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
		}
		m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)")
				% start.x % start.y % end.x % end.y
			  << endl
			  << boost::format(R"(    <color r="%1%" g="%2%" b="%3%" a="%4%" />)")
				% rgbColor.r % rgbColor.g % rgbColor.b % rgbColor.a
			  << endl
			  << "  </line>"
			  << endl;
	}

	// Этот метод должен быть вызван в конце рисования
	void EndDraw()
	{
		// Реализация остается без изменения
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}

private:
	ostream& m_out;
	bool m_drawing = false;
};
} // namespace modern_graphics_lib_pro

// Пространство имен приложения (доступно для модификации)
namespace app
{
class CRendererAdapter : public graphics_lib_pro::ICanvas
{
public:
	CRendererAdapter(modern_graphics_lib_pro::CModernGraphicsRenderer& render)
		: m_render(render)
		, m_point(0, 0)
		, m_rgbColor(0, 0, 0, 0)
	{
		m_render.BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_point = modern_graphics_lib_pro::CPoint(x, y);
	}

	void LineTo(int x, int y) override
	{
		m_render.DrawLine(m_point, modern_graphics_lib_pro::CPoint(x, y), m_rgbColor);
		MoveTo(x, y);
	}
	void SetColor(uint32_t rgbColor) override
	{
		m_rgbColor.r = ((rgbColor >> 16) & 0xFF) / 255.f;
		m_rgbColor.g = ((rgbColor >> 8) & 0xFF) / 255.f;
		m_rgbColor.b = (rgbColor & 0xFF) / 255.f;
		m_rgbColor.a = 1.0;
	}

private:
	modern_graphics_lib_pro::CPoint m_point;
	modern_graphics_lib_pro::CModernGraphicsRenderer& m_render;
	modern_graphics_lib_pro::CRGBAColor m_rgbColor;
};

void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0x0000FF);
	CRectangle rectangle({ 30, 40 }, 18, 24, 0xFF0000);

	// TODO: нарисовать прямоугольник и треугольник при помощи painter
	painter.Draw(rectangle);
	painter.Draw(triangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib_pro::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib_pro::CModernGraphicsRenderer renderer(cout);
	(void)&renderer; // устраняем предупреждение о неиспользуемой переменной

	// TODO: при помощи существующей функции PaintPicture() нарисовать
	// картину на renderer
	// Подсказка: используйте паттерн "Адаптер"
	CRendererAdapter adapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(adapter);
	PaintPicture(painter);
}
} // namespace app