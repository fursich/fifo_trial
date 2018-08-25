require 'spec_helper'
require_relative '../lib/fifo.bundle'

RSpec.describe 'Fifo (c ext)' do
  it_behaves_like 'stack' do
    let(:base_stack) { Fifo.new }
  end
end
