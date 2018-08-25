require 'benchmark'
require_relative '../lib/lifo.bundle'
require_relative '../lib/rb_lifo.rb'

BENCHMARK_COUNT = 100
UNIT_ITERATION = 100000

Benchmark.bm BENCHMARK_COUNT do |r|  
  r.report 'LIFO (c-ext)' do
    f = Lifo.new
    UNIT_ITERATION.times do |n|
      f.push(n)
    end
    UNIT_ITERATION.times do |n|
      f.pop
    end
  end

  r.report 'LIFO (ruby)' do
    f = RBLifo.new
    UNIT_ITERATION.times do |n|
      f.push(n)
    end
    UNIT_ITERATION.times do |n|
      f.pop
    end
  end
end

