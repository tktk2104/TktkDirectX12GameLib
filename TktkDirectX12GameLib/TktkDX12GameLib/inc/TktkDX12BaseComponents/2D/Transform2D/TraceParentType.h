#ifndef TRACE_PARENT_TYPE_H_
#define TRACE_PARENT_TYPE_H_

namespace tktk
{
	// 親のTransformとの関係性の種類
	enum class TraceParentType
	{
		// 親の座標のみを参照する
		tracePos				= 1 << 0,

		// 親のスケールのみを参照する
		traceScale				= 1 << 1,

		// 親の回転のみを参照する
		traceRotation			= 1 << 2,

		// 親のTransformを参照しない
		notTrace = 0,

		// 親の座標とスケールを参照する
		tracePosAndScale		= tracePos | traceScale,

		// 親の座標と回転を参照する
		tracePosAndRotation		= tracePos | traceRotation,

		// 親のスケールと回転を参照する
		traceScaleAndRotation	= traceScale | traceRotation,

		// 親のTransformを完全に参照する
		trace_All				= tracePos | traceScale | traceRotation,
	};
}
#endif // !TRACE_PARENT_TYPE_H_