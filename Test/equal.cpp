#include "stdafx.h"

namespace ParallelSTL_Tests
{
	TEST_CLASS(EqualElementTest)
	{
		template<typename _IterCat>
		struct EqualAlgoTest :
			public AlgoTest<EqualAlgoTest<_IterCat>, _IterCat, size_t, bool>
		{
			bool _Equal;
		public:
			EqualAlgoTest(bool _IsEqual) : _Equal(_IsEqual)
			{
				auto _Start = rand();
				std::iota(std::begin(_Ct), std::end(_Ct), _Start);
				_Ct_copy.resize(_Ct.size());
				std::iota(std::begin(_Ct_copy), std::end(_Ct_copy), _Start);

				auto _Pos = rand() % _Ct.size();
				_Ct[_Pos] = _IsEqual ? _Ct[_Pos] : 0;
			}

			~EqualAlgoTest()
			{
				if (_Equal)
					Assert::IsTrue(_Result);
				else Assert::IsFalse(_Result);
			}

			std::function<bool(size_t, size_t)> equal()
			{
				return std::function<bool(size_t, size_t)>([](size_t _First, size_t _Next){
					return _First == _Next;
				});
			}
		};

		TEST_METHOD(EqualElementEdgeCases)
		{
			// Compare empty collections
			std::vector<int> vec_empty, vec_empty2;
			Assert::IsTrue(equal(par, std::begin(vec_empty), std::end(vec_empty), std::begin(vec_empty2)));

			// Last element different
			std::vector<int> vec_not_equal_end = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, vec_not_equal2_end = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 11 };
			Assert::IsFalse(equal(par, std::begin(vec_not_equal_end), std::end(vec_not_equal_end), std::begin(vec_not_equal2_end)));

			// First element different
			std::vector<int> vec_not_equal_begin = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }, vec_not_equal2_begin = { 2, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
			Assert::IsFalse(equal(par, std::begin(vec_not_equal_begin), std::end(vec_not_equal_begin), std::begin(vec_not_equal2_begin)));

			// Compare empty collection to another none empty
			Assert::IsTrue(equal(par, std::begin(vec_empty), std::end(vec_empty), std::begin(vec_not_equal2_end)));

			// Equals with 4 input iterators

			// Compare empty collections
			Assert::IsTrue(equal(par, std::begin(vec_empty), std::end(vec_empty), std::begin(vec_empty2), std::end(vec_empty2)));

			// Last element different
			Assert::IsFalse(equal(par, std::begin(vec_not_equal_end), std::end(vec_not_equal_end), std::begin(vec_not_equal2_end), std::end(vec_not_equal2_end)));

			// First element different
			Assert::IsFalse(equal(par, std::begin(vec_not_equal_begin), std::end(vec_not_equal_begin), std::begin(vec_not_equal2_begin), std::end(vec_not_equal2_begin)));

			// Compare empty collection to another none empty
			Assert::IsTrue(equal(par, std::begin(vec_empty), std::end(vec_empty), std::begin(vec_not_equal2_end), std::end(vec_not_equal2_end)));
		}

		template<typename _IterCat>
		void RunEqualElement(bool _Equal)
		{
			{  // seq
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(seq, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest()));
			}

			{  //par
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(par, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest()));
			}

			{  //vec
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(vec, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest()));
			}
		}

		TEST_METHOD(EqualElement)
		{
			RunEqualElement<random_access_iterator_tag>(true);
			RunEqualElement<forward_iterator_tag>(true);
			RunEqualElement<input_iterator_tag>(true);

			RunEqualElement<random_access_iterator_tag>(false);
			RunEqualElement<forward_iterator_tag>(false);
			RunEqualElement<input_iterator_tag>(false);
		}

		template<typename _IterCat>
		void RunEqualElementPredicate(bool _Equal)
		{
			{  // seq
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(seq, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.equal()));
			}

			{  //par
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(par, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.equal()));
			}

			{  //vec
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(vec, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.equal()));
			}
		}

		TEST_METHOD(EqualElementCallback)
		{
			RunEqualElementPredicate<random_access_iterator_tag>(true);
			RunEqualElementPredicate<forward_iterator_tag>(true);
			RunEqualElementPredicate<input_iterator_tag>(true);

			RunEqualElementPredicate<random_access_iterator_tag>(false);
			RunEqualElementPredicate<forward_iterator_tag>(false);
			RunEqualElementPredicate<input_iterator_tag>(false);	
		}

		template<typename _IterCat>
		void RunEqualElement4Params(bool _Equal)
		{
			{  // seq
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(seq, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest()));
			}

			{  //par
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(par, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest()));
			}

			{  //vec
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(vec, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest()));
			}
		}

		TEST_METHOD(EqualElement4Params)
		{
			RunEqualElement4Params<random_access_iterator_tag>(true);
			RunEqualElement4Params<forward_iterator_tag>(true);
			RunEqualElement4Params<input_iterator_tag>(true);

			RunEqualElement4Params<random_access_iterator_tag>(false);
			RunEqualElement4Params<forward_iterator_tag>(false);
			RunEqualElement4Params<input_iterator_tag>(false);
		}

		template<typename _IterCat>
		void RunEqualElementPredicate4Params(bool _Equal)
		{
			{  // seq
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(seq, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest(), _Alg.equal()));
			}

			{  //par
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(par, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest(), _Alg.equal()));
			}

			{  //vec
				EqualAlgoTest<_IterCat> _Alg(_Equal);
				_Alg.set_result(equal(vec, _Alg.begin_in(), _Alg.end_in(), _Alg.begin_dest(), _Alg.end_dest(), _Alg.equal()));
			}
		}

		TEST_METHOD(EqualElementCallback4Params)
		{
			RunEqualElementPredicate4Params<random_access_iterator_tag>(true);
			RunEqualElementPredicate4Params<forward_iterator_tag>(true);
			RunEqualElementPredicate4Params<input_iterator_tag>(true);

			RunEqualElementPredicate4Params<random_access_iterator_tag>(false);
			RunEqualElementPredicate4Params<forward_iterator_tag>(false);
			RunEqualElementPredicate4Params<input_iterator_tag>(false);
		}
	};
} // ParallelSTL_Tests
