require 'spec_helper'
require_relative '..//lib/rb_fifo.rb'

RSpec.describe do
  it_behaves_like 'stack' do
    let(:base_stack) { RBFifo.new }
  end
end
