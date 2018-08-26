require 'spec_helper'
require_relative '../bin/clifo.bundle'

RSpec.describe 'LIFO (usng c struct)' do
  it_behaves_like 'stack' do
    let(:base_stack) { CLifo.new }
  end
end
