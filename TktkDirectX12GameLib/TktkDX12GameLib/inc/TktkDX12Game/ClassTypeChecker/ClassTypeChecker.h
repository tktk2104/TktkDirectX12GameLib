#ifndef CLASS_TYPE_CHECKER_H_
#define CLASS_TYPE_CHECKER_H_

namespace tktk
{
	// クラスの型情報に対応したuint型を取得するクラス
	class ClassTypeChecker
	{
	public:

		// テンプレート引数の型に対応したuint型を取得する
		template <class T>
		static unsigned int getClassId();

	private:

		static unsigned int m_nextClassId;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	// テンプレート引数の型に対応したuint型を取得する
	template<class T>
	inline unsigned int ClassTypeChecker::getClassId()
	{
		static const unsigned int classId = m_nextClassId++;
		return classId;
	}
}
#endif // !CLASS_TYPE_CHECKER_H_