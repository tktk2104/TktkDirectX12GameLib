#ifndef ELAPSED_TIMER_H_
#define ELAPSED_TIMER_H_

/* std::clock_t */
#include <ctime>

namespace tktk
{
	// 経過時間を管理するタイマー
	class ElapsedTimer
	{
	public:

		ElapsedTimer();
		~ElapsedTimer();

		ElapsedTimer(const ElapsedTimer& other) = delete;
		ElapsedTimer& operator = (const ElapsedTimer& other) = delete;

	public:

		void reset();

		void update();

		// 前フレームとの時間の差を求める
		float deltaTime() const;

		// 前フレームとの時間の差を求める（TimeScaleを無視）
		float noScaleDeltaTime() const;

		// プログラムが起動してからの時間（秒）を返す
		float getCurTimeSec() const;

		// 最大のdeltaTimeの値を設定（正の数）
		void setMaximumDeltaTime(float maximumDeltaTime);

		// 時間の経過速度割合を取得する
		float getTimeScale() const;

		// 時間の経過速度割合を設定する（0.0～float_max）
		void setTimeScale(float timeScaleRate);

		// 瞬間的なFPSを取得する
		float fps() const;

		// 基準となるFPSを設定する
		void setBaseFps(unsigned int baseFps);

		// 基準となるFPSを取得する
		unsigned int getBaseFps() const;

	private:

		// プログラムの開始時間
		std::clock_t m_startTime;

		// 前フレームの時間
		std::clock_t m_preTime;

		// 合計時間
		float m_totalTime;

		// 前フレームとの時間の差
		float m_deltaTime;

		// 最大のdeltaTimeの値
		float m_maximumDeltaTime{ 0.1f };

		// 時間の経過速度割合
		float m_timeScaleRate{ 1.0f };

		// 基本となるfps
		unsigned int m_baseFps;
	};
}
#endif // !ELAPSED_TIMER_H_