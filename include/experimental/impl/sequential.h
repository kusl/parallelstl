#pragma once

#ifndef _IMPL_SEQUENTIAL_H_
#define _IMPL_SEQUENTIAL_H_

#include <numeric>

namespace std {
	namespace experimental {
		namespace parallel {

			template<class _InIt, class _Diff, class _Pr>
			inline _InIt for_each_n(_InIt _First, _Diff _Count, _Pr _Pred)
			{
				for (; 0 < _Count; --_Count, ++_First)
					_Pred(*_First);

				return _First;
			}

			template <class _InIt, class _Ty, class _BinOp>
			inline typename _Ty reduce(_InIt _First, _InIt _Last, _Ty _Init, _BinOp _Op)
			{
				return std::accumulate(_First, _Last, _Init, _Op);
			}

			template <class _InIt, class _Ty = std::iterator_traits<_InIt>::value_type>
			inline typename _Ty reduce(_InIt _First, _InIt _Last, _Ty _Init)
			{
				return std::accumulate(_First, _Last, _Init, std::plus<>());
			}

			template <class _InIt>
			inline typename std::iterator_traits<_InIt>::value_type reduce(_InIt _First, _InIt _Last)
			{
				return std::accumulate(_First, _Last, std::iterator_traits<_InIt>::value_type{}, std::plus<>());
			}

			template<class _InIt, class _OutIt, class _Ty = std::iterator_traits<_InIt>::value_type, class _BinOp = std::plus<_Ty>>
			inline _OutIt exclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest, _Ty _Init = _Ty(), _BinOp _Op = _BinOp())
			{
				for (; _First != _Last; ++_First, ++_Dest) {
					*_Dest = _Init;
					_Init = _Op(_Init, *_First);
				}

				return _Dest;
			}

			template<class _InIt, class _OutIt, class _Ty = std::iterator_traits<_InIt>::value_type>
			inline _OutIt exclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest, _Ty _Init)
			{
				return exclusive_scan(_First, _Last, _Dest, _Init, std::plus<>());
			}

			template<class _InIt, class _OutIt>
			inline _OutIt exclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest)
			{
				return exclusive_scan(_First, _Last, _Dest, std::iterator_traits<_InIt>::value_type{}, std::plus<>());
			}

			template<class _InIt, class _OutIt, class _Ty = std::iterator_traits<_InIt>::value_type, class _BinOp = std::plus<_Ty>>
			inline _OutIt inclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest, _Ty _Init = _Ty(), _BinOp _Op = _BinOp())
			{
				for (; _First != _Last; ++_First, ++_Dest) {
					_Init = _Op(_Init, *_First);
					*_Dest = _Init;
				}

				return _Dest;
			}

			template<class _InIt, class _OutIt, class _Ty = std::iterator_traits<_InIt>::value_type>
			inline _OutIt inclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest, _Ty _Init)
			{
				return inclusive_scan(_First, _Last, _Dest, _Init, std::plus<>());
			}

			template<class _InIt, class _OutIt>
			inline _OutIt inclusive_scan(_InIt _First, _InIt _Last, _OutIt _Dest)
			{
				return inclusive_scan(_First, _Last, _Dest, std::iterator_traits<_InIt>::value_type{}, std::plus<>());
			}
		}
	}
} // std::experimental::parallel

#endif // _IMPL_SEQUENTIAL_H_


