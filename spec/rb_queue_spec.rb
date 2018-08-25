require 'spec_helper'
require_relative '..//lib/rb_fifo.rb'

RSpec.describe 'FIFO (ruby)' do
  it_behaves_like 'queue' do
    let(:base_queue) { RBFifo.new }
  end
end
