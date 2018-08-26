require 'spec_helper'
require_relative '../bin/lifo.bundle'

RSpec.describe 'LIFO (c ext)' do
  it_behaves_like 'stack' do
    let(:base_stack) { Lifo.new }
  end
end
